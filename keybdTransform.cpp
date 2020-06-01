
#include <iostream>
#include <string>


using namespace std;

//find original location of characters in out input string

void findOriginalLocation(char c, int &originalRow, int &originalColumn){
    string row1 = "1234567890";
    string row2 = "QWERTYUIOP";
    string row3 = "ASDFGHJKL;";
    string row4 = "ZXCVBNM,./";


//if we can find our character in the row

    if (row1.find(c)!=std::string::npos){
        originalRow = 0;

        // column will be index where element is found in correct row

        originalColumn = row1.find(c);
    }

    else if(row2.find(c)!=std::string::npos){
        originalRow = 1;
        originalColumn = row2.find(c);
    }

    else if(row3.find(c)!=std::string::npos){
        originalRow = 2;
        originalColumn = row3.find(c);
    }
    
    else if(row4.find(c)!=std::string::npos){
        originalRow = 3;
        originalColumn = row4.find(c);
    }

    else{
        cout << endl << "Error! Character in string is not in keyboard." << endl;
    }
}

void shift(char arr[][10], int numShift){
    string keybd="";
    for(int row = 0; row<4;row++){
        for(int col = 0; col<10; col++){
            keybd += arr[row][col];
        }
    }
    
    
    
    int n = keybd.length();
    
    //substring that will be the string of characters that will get shifted to the 'front'
    
    string newKeybd = keybd.substr(n-numShift);
    
    //add substring of rest of characters --> new "rotated"/shifted string
    

    newKeybd += keybd.substr(0,n - numShift);

    //now let's put this string into our array!


    int i = 0;
    
    for (int row=0;row<4;row++){
        for(int col=0;col<10;col++){
            arr[row][col] = newKeybd[i];
            cout << arr[row][col];
            i++;
        }
        cout<<endl;
    }
    cout<<endl;

}

//reverse string

string reverse(string str){
    string strReversed;
    int n = str.length();
    for (int i = 0; i<n;i++){
        strReversed += str[n-i-1];
    }
    return strReversed;
}

//gameplan: we will have 4 strings corresponding to each row of our 2D keybd matrix
//for a horizontal flip:reverse each string and then update value in 2D matrix
//for a vertical flip: reverse the order of rows when we put them in back into 2D matrix

void hFlip(char keybd[][10]){
    string keybdStr="";
    for(int row = 0; row<4;row++){
        for(int col = 0; col<10; col++){
            keybdStr += keybd[row][col];
        }
    }
    string row1 = keybdStr.substr(0,10);
    
    string row2 = keybdStr.substr(10,10);
    
    string row3 = keybdStr.substr(20,10);
    
    string row4 = keybdStr.substr(30,10);
   

    keybdStr= reverse(row1) + reverse(row2) + reverse(row3) + reverse(row4);

    cout << endl<< reverse(row1) << endl<< reverse(row2) << endl<< reverse(row3) << endl<< reverse(row4) << endl << endl;

    //now let's put this string into our array!

    int i = 0;
    
    for (int row=0;row<4;row++){
        for(int col=0;col<10;col++){
            keybd[row][col] = keybdStr[i];
            i++;
        }
    }

}

//vertical flip

void vFlip(char keybd[][10]){
    string keybdStr="";
    for(int row = 0; row<4;row++){
        for(int col = 0; col<10; col++){
            keybdStr += keybd[row][col];
        }
    }
    string row4 = keybdStr.substr(0,10);
    
    string row3 = keybdStr.substr(10,10);
    
    string row2 = keybdStr.substr(20,10);
    
    string row1= keybdStr.substr(30,10);
   

    keybdStr= row1 + row2 + row3 + row4;

    cout << endl<< row1 << endl<< row2 << endl<< row3 << endl<< row4 << endl <<endl;

    //now let's put this string into our array!

    int i = 0;
    
    for (int row=0;row<4;row++){
        for(int col=0;col<10;col++){
            keybd[row][col] = keybdStr[i];
            i++;
        }
    }

}

int main(){

    int shiftNumStart;
    string steps = "HHVS12VHVHS3H";
    string textToTransform = "KLEINBOTTLES";
    string transformedText;
    
    int originalRow;
    int originalColumn;

    char keybd[4][10] = {
        {'1','2','3','4','5','6','7','8','9','0'},
        {'Q','W','E','R','T','Y','U','I','O','P'},
        {'A','S','D','F','G','H','J','K','L',';'},
        {'Z','X','C','V','B','N','M',',','.','/'}
    };

    string shiftNumDigits;
    int shiftNum;
    int hCount = 0;
    int vCount = 0;

// get all the "steps"/transformations from input string 
//then perform appropriate step(s)


    for (int i = 0; i <steps.length();i++){
        if(steps[i]== 'H'){

           hCount++;
            
        }
            
        else if(steps[i]=='V'){

            vCount++;
            
        }
              
        else if (steps[i]=='S'){

            //the order for H flips and V flips doesnt matter
            // HVHV is the same as VHHV
            //so even occurences of Hs or Vs cancel out 
            //no need to perform those actions!
            //shifts order does matter htough so the Hs and Vs only cancel out before/after an S shift

            if(hCount%2==1){
                cout << "Horizontal Flip" <<endl<<"New Keyboard:"<<endl<<endl;
                hFlip(keybd);
            }

            if(vCount%2==1){
                cout << "Vertical Flip" <<endl<<"New Keyboard:"<<endl<<endl;
                vFlip(keybd);
            }

            hCount = 0;
            vCount = 0;

            shiftNumStart=i;
            
            while(isdigit(steps[i+1])){
                i++;
            }

            //create substring of the digits

            shiftNumDigits=steps.substr(shiftNumStart+1,i);

            //convert string to integer

            shiftNum = stoi(shiftNumDigits);

            cout<< "Shift By " << shiftNum <<endl << "New Keyboard:" <<endl<<endl;

            //we take modulus 40 since getting to 40 is a 'restart' aka shifting 40 characters is the same as no shift at all

            shift(keybd,shiftNum%40);

            
        }    

    }

    //check one last time since our step string might not end in an S and we have to check again for Hs and Vs

    if(hCount%2==1){
        cout << "Horizontal Flip" <<endl<<"New Keyboard:"<<endl<<endl;
        hFlip(keybd);
    }

    if(vCount%2==1){
        cout << "Vertical Flip" <<endl<<"New Keyboard:"<<endl<<endl;
        vFlip(keybd);
    }

    //output transformed text --> use original locations of characters in input string to find elements in our transformed 2D array

    
    for (int j = 0; j<textToTransform.length();j++){
        findOriginalLocation(textToTransform[j], originalRow, originalColumn);
        
        transformedText += keybd[originalRow][originalColumn];
    }

    cout << endl << "The initial text was: " << textToTransform <<endl;
    cout<< "The new text is: " << transformedText <<endl;
}
