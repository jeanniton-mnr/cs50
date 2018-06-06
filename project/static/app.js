
// Execute when the DOM is fully loaded
$(document).ready(function() {

	//	Header
	let $header = $("header"),
	//	search form
		$search_form = $("#search-form"),
	//	Search input
		$search = $('input[name="search"]'),
	// Main content
		$content = $("#content"),
	// Handlebars template to render definiton data
		dict_template = Handlebars.compile($("#dict-template").html());


	/*
	* Banner background Transition
	* code adapted from: https://codepen.io/dudleystorey/pen/qEoKzZ
	*/

	// Image file name
	let bgImageArray = ["uluwatu.jpg", "carezza-lake.jpg", "batu-bolong-temple.jpg"],
	// Base URL of image location
	base = "https://s3-us-west-2.amazonaws.com/s.cdpn.io/4273/full-",
	// Background change interval
	secs = 4;
	// caches images to avoid white flash between background replacements
	bgImageArray.forEach(function(img){
	    new Image().src = base + img;
	}),
	// current background image index
	k = 0;

	let backgroundSequence = function(){
		window.clearTimeout();
		// background should cover the entire element
		$header[0].style.backgroundSize ="cover";
		// current background url
		let url = base + bgImageArray[k];
		// set/active current background
		$header[0].style.backgroundImage = "url(" + url + ")";
		// update k (background image index)
		if ((k + 1) === bgImageArray.length) {k = 0;}
		else { k++; }
		// set timeout to change to next background
		setTimeout(function() { backgroundSequence() }, (secs * 1000));
	};
	// start sequence
	backgroundSequence();


	// Configure typeahead.js for search input
	$search.typeahead({
	  hint: true,
	  highlight: true,
	  minLength: 1
	},
	{
	  source: suggestions,
	  templates: {
	  	suggestion: function (data) {
		        return '<div>' + data + '</div>';
		    }
		}
	});

	// Get definition of selected suggestion
	$search.on("typeahead:selected", function(eventObject, suggestion, name) {
		// Define and render definition of suggestion
	    define(suggestion);
	});

	// Get definition on form submission
	$("#search-form").submit(function( event ) {
		define($search.val());
		event.preventDefault();
		return false;
	});

	// Query suggestions for value entered in input
	function suggestions(query, syncResults, asyncResults)
	{
	    // Get suggestions list matching search input (asynchronously)
	    let param = {lemma: query};
	    // url sample: https://dry-ravine-39666.herokuapp.com/suggestions?lemma=app
	    $.getJSON("https://dry-ravine-39666.herokuapp.com/suggestions", param)
		.done(function(data) {
			// Call typeahead's callback with suggestions
			asyncResults(data.suggestions);
			console.log("done");
		})
		.fail(function() {
			console.log("fail");
		});
	}

	// Get definition of query and render it to main content of page.
	function define(query){
		// Set request parameters
		let param = {lemma: query};
		// Get definition of `query`
		$.getJSON("https://dry-ravine-39666.herokuapp.com/define", param)
		.done(function(data){
			// Display result on main-content section of the page
			let html = dict_template(data);
			$content.html(html);
		}).fail(function(){
			console.log("fail");
		});
	}

	// Speach the defined search/word
	function speech(){
		let to_speech = $(".dict-lemma").first().html();
		responsiveVoice.speak(to_speech);
	}
	// Make speech function accessible outside of jQuery ready for
	// inline javascript use in template
	window.speech = speech;

	// Update form position so it always visible on the viewport
	function update(){
		//
		if($header.inView())
		{
			$search_form.removeClass("form-float");
		}else
		{
			$search_form.addClass("form-float");
		}
	}
	$( window ).resize(update);
	$( window ).scroll(update);
	$search.focus();

// End of $(document).ready
});