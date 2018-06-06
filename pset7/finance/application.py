# As a reminder, your API key is: WQCQGZE2CEWDWNMC

import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# CONSTANT IDENTIFIER FOR TRANSACTION
TRANSACTION_TYPE_PURCHASE = 1
TRANSACTION_TYPE_SELL = 2

# Ensure environment variable is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Get the user's information and portfolio
    user = db.execute("SELECT * FROM users WHERE id = :user_id", user_id=session["user_id"])
    portfolio = db.execute("SELECT * FROM portfolio \
                                WHERE user_id = :user_id",
                        user_id=session["user_id"])

    # Template variables
    balance_t = user[0]["cash"]
    grand_total_t = balance_t
    stocks_t = []
    # Build stocks for template
    for stock in portfolio:
        found = lookup(stock["symbol"])
        stocks_t.append({
            "name": found["name"],
            "symbol": found["symbol"],
            "shares": stock["shares"],
            "price": found["price"],
            "total": float(stock["shares"]) * float(found["price"])
        })
        grand_total_t = grand_total_t + float(stock["shares"]) * float(found["price"])

    return render_template("index.html", balance=balance_t, stocks=stocks_t, grand_total=grand_total_t)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":
        # The form should returns the symbol and the number of shares

        # Ensure symbol was submitted
        formSymbol = request.form.get("symbol")

        if not formSymbol:
            return apology("You must provide a symbol", 400)

        # Lookup for symbol price
        found = lookup(formSymbol)

        if not found:
            return apology("The symbol you provided was not found", 400)

        # Ensure the number of shares was submitted
        formShares = request.form.get("shares")
        if not formShares:
            return apology("You must provide a share amount", 400)
        # Convert shares from str to int
        try:
            formShares = int(formShares)
        except:
            return apology("Shares number is not valid", 400)

        # Check if shares is more than 0
        if formShares <= 0:
            return apology("Share number is not valid", 400)

        # Get the user's information submitting this form
        user = db.execute("SELECT * FROM users WHERE id = :user_id", user_id=session["user_id"])

        purchase_amount = found["price"] * formShares

        # Check if user has sufficient fund
        if float(user[0]["cash"]) < purchase_amount:
            return apology("Not suffucient fund for this transaction", 400)

        # Update the user portfolio
        portfolio = db.execute("SELECT * FROM portfolio \
                                WHERE user_id = :user_id \
                                AND symbol = :symbol",
                                user_id=session["user_id"],
                                symbol=found["symbol"])

        # Check if the user already has this stock/symbol in his portfolio
        if portfolio:
            db.execute("UPDATE portfolio \
                        SET shares = :shares \
                        WHERE user_id = :user_id \
                        AND symbol = :symbol",
                        shares=portfolio[0]["shares"] + formShares,
                        user_id=session["user_id"],
                        symbol=found["symbol"] )
        # Otherwise, update this stock/symbol in the user's portfolio
        else:
            db.execute("INSERT INTO portfolio \
                        (user_id, symbol, shares) \
                        VALUES (:user_id, :symbol, :shares)",
                        user_id = session["user_id"],
                        symbol = found["symbol"],
                        shares = formShares )

        # Calculate and update reminded cash
        reminded_cash = float(user[0]["cash"]) - purchase_amount
        db.execute("UPDATE users SET cash=:cash WHERE id=:user_id", cash = reminded_cash, user_id = session["user_id"])

        # Register the purchase transaction
        db.execute("INSERT INTO transactions \
                                (user_id, type, symbol, shares, price) \
                                VALUES (:user_id, :type, :symbol, :shares, :price)",
                    user_id=session["user_id"],
                    type=TRANSACTION_TYPE_PURCHASE,
                    symbol=found["symbol"],
                    shares=formShares,
                    price=str(found["price"]))

        # Redirect user to home page
        flash('You have successfully purchased the stock')
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # Get user transactions
    transactions = db.execute("SELECT * FROM transactions WHERE user_id=:user_id", user_id=session["user_id"])
    # Format transactions for template
    for transaction in transactions:
        if int(transaction["type"]) == TRANSACTION_TYPE_SELL:
            transaction["shares"] = "-" + str(transaction["shares"])

    # Render page
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reached route via POST
    if request.method == "POST":
        # Look up quote name for this symbol.
        found = lookup(request.form.get("symbol"))

        if not found:
            return apology("Not a valid symbol", 400)

        return render_template("quoted.html", stock=found)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST
    if request.method == "POST":
        # Ensure username was submitted
        formUsername = request.form.get("username")
        if not formUsername:
            return apology("username field can't be empty", 400)

        # Check to see if username already exist
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=formUsername)

        if len(rows) > 0:
            return apology("username already exists", 400)

        # Ensure password is submitted and matched confirmation
        formPassword = request.form.get("password")
        formConfirmation = request.form.get("confirmation")

        if not formPassword:
            return apology("password field can't be empty", 400)

        # Check to see if password matches confirmation
        if formPassword != formConfirmation:
            return apology("passwords don't match", 400)

        # Hash the password
        hashPassword = generate_password_hash(formPassword)

        # Insert new user in DATABASE
        newUser = db.execute("INSERT INTO users (username, hash) \
                             VALUES (:username, :hash)",
                             username=formUsername,
                             hash=hashPassword)

        if not newUser:
            return apology("There was a problem creating new user", 403)

        # Save new user in session
        session["user_id"] = newUser

        # Redirect user to home page
        flash('You were successfully logged in')
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # User reaches root via post
    if request.method == "POST":
        # Get and "validate" form symbol
        formSymbol = request.form.get("symbol")

        # Ensure form sybol was submitted
        if not formSymbol:
            return apology("You must provide a symbol", 400)

        # Lookup for symbol information (: price, name, symbol)
        found = lookup(formSymbol)

        if not found:
            return apology("The symbol you provided was not found", 400)

        # Retrive symbol from user portfolio
        portfolio = db.execute("SELECT * FROM portfolio \
                                WHERE user_id = :user_id \
                                AND symbol = :symbol",
                            user_id=session["user_id"],
                            symbol=formSymbol)
        if not portfolio:
            return apology("You can't sell a stock/symbol you don't have", 400)

        # Get and "validate" form shares
        formShares = request.form.get("shares")
        # Convert shares from str to int
        try:
            formShares = int(formShares)
        except:
            return apology("Shares number is not valid", 400)

        # Check if user can sell that amount of the stock
        if formShares > int(portfolio[0]["shares"]):
            return apology("You can't sell that amount of shares.", 400)

        # Update shares amount\shares left
        db.execute("UPDATE portfolio \
                        SET shares = :shares \
                        WHERE user_id = :user_id \
                        AND symbol = :symbol",
                    shares=int(portfolio[0]["shares"]) - formShares,
                    user_id=session["user_id"],
                    symbol=formSymbol)

        # Register the sell transaction
        db.execute("INSERT INTO transactions \
                                (user_id, type, symbol, shares, price) \
                                VALUES (:user_id, :type, :symbol, :shares, :price)",
                    user_id = session["user_id"],
                    type=TRANSACTION_TYPE_SELL,
                    symbol=found["symbol"],
                    price=found["price"],
                    shares=formShares)

        # Get user informartion from DB
        user = db.execute("SELECT * FROM users WHERE id = :user_id", user_id=session["user_id"])

        # Calculate and Update reminded cash
        total_cash = float(user[0]["cash"]) + (formShares * found["price"])
        db.execute("UPDATE users SET cash=:cash WHERE id=:user_id", cash = total_cash, user_id = session["user_id"])

        # Register the purchase transaction
        db.execute("INSERT INTO transactions \
                                (user_id, type, symbol, shares, price) \
                                VALUES (:user_id, :type, :symbol, :shares, :price)",
                user_id=session["user_id"],
                type=TRANSACTION_TYPE_PURCHASE,
                symbol=found["symbol"],
                shares=formShares,
                price=found["price"])

        # Return user to to home page with successful flash message
        flash('You have successfully sold that/those(s) stocks.')
        return redirect("/")
    else:
        stocks = db.execute("SELECT symbol FROM portfolio WHERE user_id = :user_id",
                    user_id=session["user_id"])
        return render_template("sell.html", stocks = stocks)


@app.route("/change_password", methods=["GET", "POST"])
@login_required
def change_password():
    """Change password of user"""
    # User reaches root via post
    if request.method == "POST":
        # Retrive user information
        user = db.execute("SELECT * FROM users WHERE user_id = :user_id", user_id=session["user_id"])
        # Old password
        oldPassword = request.form.get("old")
        if not old:
            return apology("You must provide the current/old password", 400)

        if user[0]["hash"] != generate_password_hash(oldPassword):
            return apology("The old password is not correct", 400)

        # New password
        newPassword = request.form.get("new")
        if not new:
            return apology("Please provide a new password", 400)

        if newPassword != request.form.get("confirmation"):
            return apology("Password confirmation doesn't match", 400)

        # Hash the new password
        hash = generate_password_hash(newPassword)
        # Update new password
        db.execute("UPDATE users SET hash=:hash WHERE id=:user_id", hash=hash, user_id=session["user_id"])

        flash("Password successfully changed")
        return redirect("/")

    # User reached via GET
    else:
        return render_template("password.html")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
