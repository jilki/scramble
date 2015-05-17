//author: Zsolt Thamo
//date: 17/05/2015
#include <iostream>
#include <string>
#include <list>

using namespace std;
 
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

//Decide if a character is a letter or not
bool Predicate(char character){
    if ((character>='A' && character<='Z') || (character>='a' && character<='z'))
        return true;
    else
        return false;
}
TEST_CASE( "decision by the function", "[is letter]" ) {
    REQUIRE( Predicate('a') == true );
    REQUIRE( Predicate('k') == true );
    REQUIRE( Predicate('z') == true );
    REQUIRE( Predicate('A') == true );
    REQUIRE( Predicate('J') == true );
    REQUIRE( Predicate('Z') == true );
    REQUIRE( Predicate('\'') == false );
    REQUIRE( Predicate('-') == false );
    REQUIRE( Predicate('\"') == false );
    REQUIRE( Predicate(',') == false );
    REQUIRE( Predicate('@') == false );
    REQUIRE( Predicate('[') == false );
    REQUIRE( Predicate('{') == false );
}

//Reverse the inner letters of a word
string ScrambleWord(string str){
    int length = str.length();
    int length2 = length;
    int a = 0;
    int b = 1;
    //check if the boundary characters are letters
    while(Predicate(str[a])==false){
        a++;
        length--;
    }
    while(Predicate(str[length2-b])==false){
        b++;
        length--;
    }
    for(int i=1;i<length/2;i++){
        //check if the actual characters are letters
        while(Predicate(str[i+a])==false){
            a++;
            length--;
        }
        while(Predicate(str[length2-i-b])==false){
            b++;
            length--;
        }
        //if we have two letters, than we swap them
        std::swap(str[i+a],str[length2-i-b]);
    }
    return str;
}

TEST_CASE( "letters reversed by the function", "[reversed letters]" ) {
    REQUIRE( ScrambleWord("abcde") == "adcbe" );
    REQUIRE( ScrambleWord("thing") == "tnihg" );
    REQUIRE( ScrambleWord("important") == "inatropmt" );
    REQUIRE( ScrambleWord("problem") == "pelborm" );
    REQUIRE( ScrambleWord("doesn't") == "dnseo't" );
    REQUIRE( ScrambleWord("Let's") == "Lte's" );
    REQUIRE( ScrambleWord("next,") == "nxet," );
    REQUIRE( ScrambleWord("\"According") == "\"Anidroccg" );
    REQUIRE( ScrambleWord("whole\"") == "wlohe\"" );
}

//Scramble the text
string ScrambleString(string text){
    string scrambled;
    size_t pos = 0;
    //slice up the text to words
    while((pos = text.find(" ")) != string::npos){
        string temp = text.substr(0,pos);
        text.erase(0, pos+1);
        //reverse the inner letters of each word
        scrambled += ScrambleWord(temp)+" ";
    }
    //one word probably left after the last space
    if(text.length()>0)
        scrambled += ScrambleWord(text);
    return scrambled;
}

TEST_CASE( "Scrambled by the function", "[Scrambled text]" ) {
    REQUIRE( ScrambleString("\"According to research at Cambridge University, it doesn't matter in what order the letters in a word are, the only important thing is that the first and last letter be at the right place. The rest can be a total mess and you can still read it without a problem. This is because the human mind does not read every letter by itself, but the word as a whole.\"") == "\"Anidroccg to rcraeseh at Cgdirbmae Utisreviny, it dnseo't mettar in waht oedrr the lrettes in a wrod are, the olny inatropmt tnihg is taht the fsrit and lsat letter be at the rhgit pcale. The rset can be a tatol mses and you can slitl raed it wuohtit a pelborm. Tihs is bsuacee the hamun mnid deos not raed erevy letter by ilestf, but the wrod as a wlohe.\"");
}

int main(int argc,char* const argv[]){
    int result = Catch::Session().run( );
    if(argc!=2){
        cout << "The program requires a string";
        return -1;
    }
    else{
        cout << ScrambleString(argv[1]);
        return 0;
    }

}
