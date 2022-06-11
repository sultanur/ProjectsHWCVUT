#include <stdlib.h>
#include <openssl/evp.h>
#include <string.h>
#include <iostream>
#define FILE_NAME "homer-simpson.bmp"
#define BUFFER_SIZE 512
using namespace std;

int main(void) {

  //unsigned char pt[1024] = "Text for rc4.";  // plaintext
  unsigned char ct[1024];  // ciphertext
  unsigned char key[EVP_MAX_KEY_LENGTH] = "It is a key";  // encryption and decryption key
  unsigned char iv[EVP_MAX_IV_LENGTH] = "initial vector";  // initialization vector
  //const char cipherName[] = "RC4";
  const EVP_CIPHER * cipher;

  OpenSSL_add_all_ciphers();
  /* ciphers and hashes could be loaded using OpenSSL_add_all_algorithms() */

  cipher = EVP_des_ecb();
  if(!cipher) {
    printf("Cipher not found.\n");
    exit(1); }

  EVP_CIPHER_CTX *ctx; // context structure
  ctx = EVP_CIPHER_CTX_new();
  if(ctx == NULL) exit(2);

//allocate buffers for header part, and for pixels
unsigned char * header = (unsigned char*)malloc(sizeof(unsigned char)*54);
unsigned char * pt = (unsigned char*)malloc(sizeof(unsigned char)*BUFFER_SIZE); // buffer for reading pixels

  int ptLength = 0; 
  int ctLength = 0;
  int ct_Length = 0;
  int pt_Length = 0;   
  int res, count = 0;
 //unsigned long data_count = 0;

	FILE * FileInput = fopen ("homer-simpson.bmp" , "r");
		if (!FileInput) {
			perror("Error when attempting to read file " FILE_NAME "./n");
				return 1; }
 //pointer on the start of file				
	fseek (FileInput, 0, SEEK_SET);
	fread(header,sizeof(unsigned char),count=14,FileInput);  //BM6  first 14 bytes of header (untill incl.offset) ,  
	unsigned long header_info_size = *(unsigned long*)(header+10);  //54
	unsigned long pt_size = *(unsigned long*)(header+2); // 2359350  // size of pixels (size of plaint text)

//cout <<"head = " << header << endl;
//cout << "header_info_size = " << header_info_size << endl;
//cout << "file_size =" << pt_size << endl;
//cout << "count =" << count << endl;	
		if(header_info_size > 54)
		header = (unsigned char*)realloc(header,sizeof(unsigned char)*pt_size); // in case if header part of file additionally consist Color Pallet (semi-optional) & Color Pallet (semi-optional) parts
		//read the rest 40 bytes of header parof file
	fread(header+count,sizeof(unsigned char),header_info_size-count,FileInput);
	

  /* Encryption */
  res = EVP_EncryptInit_ex(ctx, cipher, NULL, key, iv);  // context init - set cipher, key, init vector
  if(res != 1) exit(3);
   //open a new file to write encrypted version
	FILE * FileOutput = fopen ("homer-simpson_enc.bmp" , "w");
	fwrite (header, sizeof (unsigned char), header_info_size, FileOutput); //write header part
 		fseek (FileInput, header_info_size, SEEK_SET);  //put pointer on the start of pixels
 		 while ((ptLength = fread (pt, sizeof (unsigned char), BUFFER_SIZE, FileInput)))
		{
			pt_Length += ptLength;		
  				res = EVP_EncryptUpdate(ctx, ct, &ctLength, pt, ptLength); // encryption of pt (pixels)				
		  		if(res != 1) exit(4);
				ct_Length += ctLength;
					fwrite (ct,sizeof(unsigned char),ctLength,FileOutput);	
		}

  fseek (FileInput, header_info_size, SEEK_SET);	
  res = EVP_EncryptFinal_ex(ctx, ct, &ctLength);  // get the remaining cypher text
  if(res != 1) exit(5); 
  ct_Length += ctLength;
	fwrite(ct,sizeof(unsigned char),ctLength,FileOutput);

	fclose(FileOutput);
	fclose(FileInput);
	//cout << "The length of the loaded PT from file:" << pt_Length << endl;
 	//cout << "Encrypted  characters = "<< ct_Length << endl;

int ptLenght1 = 0;
int pt_Lenght1 = 0;
int ctLenght = 0;
int ct_Lenght = 0;
 
 /* Decryption */  
  res = EVP_DecryptInit_ex(ctx, cipher, NULL, key, iv);  // context init for decryption
  if(res != 1) exit(3);

  FILE * FileEncInput = fopen ("homer-simpson_enc.bmp", "r");  // opening previuos encrypted file
  FILE * FileDecOutput = fopen ("homer-simpson_dec.bmp", "w");   // opening a new file for the result of decryption 
 
	fseek (FileEncInput, 0, SEEK_SET);
 	fwrite(header,sizeof(unsigned char), header_info_size, FileDecOutput);//write to a new file header part
 	fseek (FileEncInput, header_info_size, SEEK_SET); //put pointer on the start of pixels
	 while(ctLenght = fread(ct,sizeof(unsigned char),BUFFER_SIZE,FileEncInput)) 
	{
		ct_Lenght += ctLenght;		
			res = EVP_DecryptUpdate(ctx, pt, &ptLenght1,  ct, ctLenght);  // decrypt cipher text (pixels)
			if(res != 1) exit(4);
  			pt_Lenght1 += ptLenght1;
				fwrite(pt,sizeof(unsigned char),ptLenght1,FileDecOutput);
	}
 
  res = EVP_DecryptFinal_ex(ctx, pt + ptLenght1, &ptLenght1);  // get the remaining plaintext
  if(res != 1) exit(5);
  pt_Lenght1 += ptLenght1;
  	fwrite(pt,sizeof(unsigned char),ptLenght1,FileDecOutput);
		fclose(FileDecOutput);
		fclose(FileEncInput);  		 
	//cout << "The length of the loaded CT from file:" << ct_Lenght << endl;	
 	//cout << "Decrypted  characters = "<< pt_Lenght1 << endl;

  			/* Clean up */
  		EVP_CIPHER_CTX_free(ctx);
		free (header);
		free (pt);

        	 exit(0);
 }

