#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <cs50.h>
#include <string.h>

string hash;
char salt[3];

int hashMatches(string password);

int main(int argc, string argv[])
{

  if (argc < 2){
    printf("Wrong number of argument!");
    return 1;
  }

  hash = argv[1];
  salt[0] = hash[0];
  salt[1] = hash[1];


  char alpha[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
            'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};


  int alpha_len = sizeof(alpha);

  for(int i=0; i < alpha_len; i++){
    char password[] = {'\0', '\0', '\0', '\0', '\0', '\0'};

    // For password[0]
    password[0] = alpha[i];
    if(hashMatches(password)){
      printf("%s", password);
      return 0;
    }

    for(int j = 0; j < alpha_len; j++){
      // For password[1]
      password[1] = alpha[j];
      if(hashMatches(password)){
        printf("%s", password);
        return 0;
      }

      for(int k = 0; k < alpha_len; k++){
        // For password[2]
        password[2] = alpha[k];
        if(hashMatches(password)){
          printf("%s", password);
          return 0;
        }

        for( int l = 0; l < alpha_len; l++){
          // For password[3]
          password[3] = alpha[l];
          if(hashMatches(password)){
            printf("%s", password);
            return 0;
          }

          for(int m = 0; m < alpha_len; m++){
            // For password[4]
            password[4] = alpha[m];
            if(hashMatches(password)){
              printf("%s", password);
              return 0;
            }

          }
        }
      }
    }
  }

  printf("Password must be longer the 5 characters or/and contain non-alpha character(s).");
  return 0;

}



// Compare if hashed/crypted password matches given hash
int hashMatches(string password)
{
  if (strcmp(crypt(password, salt), hash) == 0)
  {
    printf("%s\n", password);
    return 1;
  }
  return 0;
}