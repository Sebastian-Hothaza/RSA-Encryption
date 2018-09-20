#include <iostream>
#include <string>
#include <vector>
#include <fstream>


#include "Encrypt.h"
#include "Decrypt.h"

using namespace std;

/*
Given an Input.txt file, this program will encrypt/decrypt the message using the RSA Encryption Algorithm
*/

//DUMPS A VECTOR TO A TEXT FILE
void DumpToText(string filename, vector <long long> Vect){ 
    ofstream OutputFile;
    OutputFile.open(filename.c_str());
    //Prints to that text file each value in the vector
    for (int i=0; i<(long long)Vect.size(); i++){
        OutputFile<<Vect[i]<<endl;
    }
    OutputFile.close();
}

string AsciiToText (vector <long long> Vect){ //TURNS ASCII VALUES TO TEXT
    //Declaring variables
    string text;
    //Taking each vector slot at a time and converting that number (which corresponds to the Ascii value) and turning it long longo text
    for (long long i=0; i<(long long)Vect.size(); i++){
        text.push_back((char)Vect[i]);
    }
    return text;
}

int main(){
	// Files to be used
	ifstream InputFile;
    ofstream EncryptedMessage;
    ofstream MessageinNumbers;
    ofstream DecryptedNumbersStream;
    ofstream DecryptedMessage;

    // Vectors
    vector <string> TextContent;

    long long p=GetP();
    long long q=GetQ();
    long long n=GetN(p,q);
    long long PHI=GetPHI(p,q);
    long long e=GetE(PHI);
    long long d=GetD(PHI, e);


	//Opening the File containing the user input
    InputFile.open("Input.txt", ios::in);
    //If file is found and thus opened, it is proccessed.
    if (InputFile.is_open()){
    	string LineofText;
        while (InputFile.good()){
            //Getting each line and assigning it to LineofText
            getline(InputFile, LineofText);
            //Only stores to vector if the string is not empty. If it is, it is ignored and the next line is examined
            if (LineofText!="")
            //Pushing that string into the vector
            TextContent.push_back(LineofText); //TODO: Change to emplace_back
        }
        //We are done with the file; all neccesary info has been gathered and it can now be closed
        InputFile.close();
    }else{
        cout<<"ERROR: Input file not found. Input.txt should be in root folder."<<endl;
        return 0;
    }
    if (TextContent.size()==0){
        cout<<"Empty text file; nothing to encrypt."<<endl;
        return 0;
    }

    vector <long long> NumberToEncrypt;
    vector <long long> EncryptedNumbers;
     //Inspecting each line of the file
    for (int i=0; i<(long long)TextContent.size(); i++){
        string text = TextContent[i];
        //Inspecting each character in that line and pushing it to NumberstoEncrypt vector.
        for (int i=0; i<(long long)text.size(); i++){
            NumberToEncrypt.push_back(text[i]);
        }
    }
    DumpToText("Input in Numbers.txt", NumberToEncrypt);

    long long m;
    //ENCRYPTING
    for (int i=0; i<(long long)NumberToEncrypt.size(); i++){
        //Taking it 1 vector slot at a time
        m = NumberToEncrypt[i];
        //Getting the encrypted value
        long long c = Encrypt(m, e, n);
        //Pushing encrypted char into vector
        EncryptedNumbers.push_back(c);
    }
    DumpToText("Encrypted Message.txt", EncryptedNumbers);

    vector <long long> DecryptedNumbers;
    //DECRYPTING
    for (long long i=0; i<(long long)EncryptedNumbers.size(); i++){
        //Taking it 1 vector slot at a time
        long long c=EncryptedNumbers[i];
        //Getting the decrypted value
        long long y=Decrypt(c, d, n);
        //Pushing de-crypted number long longo vector
        DecryptedNumbers.push_back(y);
    }

    //DUMPING DE-CRYPTED NUMBERS to text file
    DumpToText("Decrypted Numbers.txt", DecryptedNumbers);

    //Turning the decrypted numbers back to text
    string FinalText = AsciiToText(DecryptedNumbers);

    //Dumping the DE-CRYPTED Message to text file
    //Creating text file
    DecryptedMessage.open ("Decrypted Message.txt");
    //Inserting the string
    DecryptedMessage<<FinalText<<endl;
    //Closing the file
    DecryptedMessage.close();

    cout<<"The value of p is: "<<p<<endl;
    cout<<"The value of q is: "<<q<<endl;
    cout<<"The value of n is: "<<n<<endl;
    cout<<"The value of PHI is: "<<PHI<<endl;
    cout<<"The value of e is: "<<e<<endl;
    cout<<"The value of d is: "<<d<<endl;
    return 0;
}
