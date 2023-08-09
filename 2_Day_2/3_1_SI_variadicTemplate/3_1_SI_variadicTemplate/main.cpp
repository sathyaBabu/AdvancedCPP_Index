//
//  main.cpp
//  3_1_SI_variadicTemplate
//
//  Created by Sathya Babu on 01/08/23.
//

#include <iostream>
using namespace std ;

// Varadic expressions are the redifined..  template over loading concept..
/*
 
 first  First    ( Rest... )  1,"Second ",2.23,"Third ",3,"Four ",4)
 first  1        ( Rest... )  "Second ",2.23,"Third ",3,"Four ",4)
 first  Second   ( Rest... )  2.23,"Third ",3,"Four ",4)
 first  2.23     ( Rest... )  "Third ",3,"Four ",4)
 first  Third    ( Rest... )  3,"Four ",4)
 first  3        ( Rest... )  "Four ",4)
 first  Four     ( Rest... )  4 )
 
 End Node 4
 
 */

template<typename T>
void print(  const T& t )
{
    cout << " End node.. "<< t << endl ;
    
}
template<typename First, typename... Rest>
void print(  const First& first , const Rest&... rest  )
{
    
    std::cout << __PRETTY_FUNCTION__ << endl ;
    
    cout <<  first << endl  << " , ";
    print( rest... );
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
//    print( 1 );
//    print( 10,20,30 );
    
    print("First ",1,"Second ",2.23,"Third ",3,"Four ",4);
    // parser to run a script -> Aravind...
    // Rajendra prasad : in case of multiple params..
    
    // server -> XML -> JSON {  [  key, value {   {   { }}} ] [] {}  }
    // 5 3 + 8 2 /
    
    // Interpreter DP..
    
    // 1 to many communication     : Observer
    // Live data                   : Observer
    // many to many communication  : Mediator
    
    
    return 0;
}
/*
 
 Hello, World!
 First
  , 1
  , Second
  , 2.23
  , Third
  , 3
  , Four
  ,  End node.. 4
 Program ended with exit code: 0
 
 
 std::cout << __PRETTY_FUNCTION__ << endl ;
 
 
 Hello, World!
 void print(const First &, const Rest &...) [First = char[7], Rest = <int, char[8], double, char[7], int, char[6], int>]
 First
  , void print(const First &, const Rest &...) [First = int, Rest = <char[8], double, char[7], int, char[6], int>]
 1
  , void print(const First &, const Rest &...) [First = char[8], Rest = <double, char[7], int, char[6], int>]
 Second
  , void print(const First &, const Rest &...) [First = double, Rest = <char[7], int, char[6], int>]
 2.23
  , void print(const First &, const Rest &...) [First = char[7], Rest = <int, char[6], int>]
 Third
  , void print(const First &, const Rest &...) [First = int, Rest = <char[6], int>]
 3
  , void print(const First &, const Rest &...) [First = char[6], Rest = <int>]
 Four
  ,  End node.. 4
 Program ended with exit code: 0
 
 */
/*
 
 infix notations
 
 ( 5 + 3 ) * ( 8 - 2 ) = 48
 5 3 + 8 2 - *         = 48
 
 
 
 
                                   2 l
            3 l                    8 r               6 l
            5 r                    8                 8 r               48
          ------                 ------            ------            ------
          values                    +                 -                 *
 
 
           lit                    (  NON LIT + * / 1  )
 
 */
/*
 
 
 
 https://api.themoviedb.org/3/movie/550?api_key=90ab00085c2a5816e9588e38f01e392a
 
 
 {
    "adult":false,
    "backdrop_path":"/hZkgoQYus5vegHoetLkCJzb17zJ.jpg",
    "belongs_to_collection":null,
    "budget":63000000,
    "genres":[
       {
          "id":18,
          "name":"Drama"
       }
    ],
    "homepage":"http://www.foxmovies.com/movies/fight-club",
    "id":550,
    "imdb_id":"tt0137523",
    "original_language":"en",
    "original_title":"Fight Club",
    "overview":"A ticking-time-bomb insomniac and a slippery soap salesman channel primal male aggression into a shocking new form of therapy. Their concept catches on, with underground \"fight clubs\" forming in every town, until an eccentric gets in the way and ignites an out-of-control spiral toward oblivion.",
    "popularity":78.699,
    "poster_path":"/pB8BM7pdSp6B6Ih7QZ4DrQ3PmJK.jpg",
    "production_companies":[
       {
          "id":508,
          "logo_path":"/7cxRWzi4LsVm4Utfpr1hfARNurT.png",
          "name":"Regency Enterprises",
          "origin_country":"US"
       },
       {
          "id":711,
          "logo_path":"/tEiIH5QesdheJmDAqQwvtN60727.png",
          "name":"Fox 2000 Pictures",
          "origin_country":"US"
       },
       {
          "id":20555,
          "logo_path":"/hD8yEGUBlHOcfHYbujp71vD8gZp.png",
          "name":"Taurus Film",
          "origin_country":"DE"
       },
       {
          "id":54051,
          "logo_path":null,
          "name":"Atman Entertainment",
          "origin_country":""
       },
       {
          "id":54052,
          "logo_path":null,
          "name":"Knickerbocker Films",
          "origin_country":"US"
       },
       {
          "id":4700,
          "logo_path":"/A32wmjrs9Psf4zw0uaixF0GXfxq.png",
          "name":"The Linson Company",
          "origin_country":"US"
       },
       {
          "id":25,
          "logo_path":"/qZCc1lty5FzX30aOCVRBLzaVmcp.png",
          "name":"20th Century Fox",
          "origin_country":"US"
       }
    ],
    "production_countries":[
       {
          "iso_3166_1":"US",
          "name":"United States of America"
       }
    ],
    "release_date":"1999-10-15",
    "revenue":100853753,
    "runtime":139,
    "spoken_languages":[
       {
          "english_name":"English",
          "iso_639_1":"en",
          "name":"English"
       }
    ],
    "status":"Released",
    "tagline":"Mischief. Mayhem. Soap.",
    "title":"Fight Club",
    "video":false,
    "vote_average":8.436,
    "vote_count":26850
 }
 */
