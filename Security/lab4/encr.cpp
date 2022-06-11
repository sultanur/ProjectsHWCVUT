//Sultanalieva Nuray, username: sultanur
#include <stdlib.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <string.h>
#include <iostream>
#define  BUFSIZE 1024


int main (int argc, char *argv[]) {

unsigned char in[BUFSIZE+EVP_MAX_BLOCK_LENGTH];
unsigned char out[BUFSIZE+EVP_MAX_BLOCK_LENGTH];
unsigned char key[EVP_MAX_KEY_LENGTH];
unsigned char iv[EVP_MAX_IV_LENGTH];
const char cipherName[] = "AES-256-CBC";
const EVP_CIPHER *cipher;

int res;

	if (argc != 4) {
	fprintf(stderr, "Usage: %s infile pubkey.pem outfile\n", argv[0]);
	exit(1);
	}

char *infile =  argv[1];
char *pubfile = argv[2];
char *outfile = argv[3];

 OpenSSL_add_all_ciphers();
 cipher = EVP_get_cipherbyname(cipherName);
	 if(!cipher) {
   	 printf("Cipher %s not found.\n", cipherName);
       	 exit(1);}
  	

	/* Load public key*/
 	EVP_PKEY * pubkey;
 	FILE *fpub = fopen (pubfile, "rb");
	     if (!fpub) {
	     	fprintf (stderr, "Public key file open failed\n");
		exit (1);}
 		

 pubkey = PEM_read_PUBKEY(fpub, NULL, NULL, NULL); //No passw protection of the key itself
	if (!pubkey) {
	   fprintf(stderr, "Public key load failed\n");
	   exit(2);}
 	
 	   fclose (fpub);

	int ekl;
	unsigned char *ek = (unsigned char *)malloc(EVP_PKEY_size(pubkey));
	if (!ek) {
	     fprintf(stderr, "Encrypted key allocation failed\n");
	     exit(3);}
	 
 /*Initialize seal*/
  EVP_CIPHER_CTX * ctx;
  ctx = EVP_CIPHER_CTX_new();
  if (ctx == NULL) exit (3);

 res = EVP_SealInit(ctx, cipher, &ek, &ekl, iv, &pubkey, 1); //initialize Seal for 1 public key
	if (res != 1) {
  	 fprintf(stderr, "SealInit failed\n");
  	 exit(3); }

   FILE *fInput = fopen(infile, "rb");
	if(!fInput) {
	fprintf (stderr, "Failed to open file\n");
		exit (3); }

//write all info for recipient....
//encryption in a loop


int iv_len = sizeof(iv);
//printf ("iv = %d\n", iv_len);
int in_lenght = 0;
int length_data = 0;
int outLength = 0;

	FILE *fOutput = fopen(outfile, "wb");
	if (!fOutput) { 
	    fprintf(stderr, "Failed to open file\n"); 
		   exit(3); }
   	rewind(fOutput);
	fprintf(fOutput, "%s %d %d" , cipherName,ekl, iv_len);
	fwrite(iv,sizeof(unsigned char),EVP_MAX_IV_LENGTH,fOutput);
	fwrite(ek,sizeof(unsigned char),ekl,fOutput); // &ek, &ekl,


  while(res = fread(in,sizeof(unsigned char),BUFSIZE,fInput))
	{
		in_lenght += res;
		if(!EVP_SealUpdate(ctx,out,&outLength,in,res)){
			fprintf(stderr, "SealUpdate is failed\n");
			exit(3); }		
		else { fwrite(out,sizeof(unsigned char),outLength,fOutput);
		length_data += outLength; }
	}
		if(!length_data) {
			fprintf(stderr,"Failed to encrypt file %s.\n",argv[1]);
			exit (3);}
	
		if(!EVP_SealFinal(ctx,out,&outLength)){
			fprintf(stderr, " SealFinal failed.\n");
			exit (3);} else { 
				fwrite(out,sizeof(unsigned char),outLength,fOutput);
				length_data += outLength;} 
				//fprintf (fOutput, "%d", length_data);
	
			


			fclose(fInput);
			fclose(fOutput);
	
	//printf("the size of Input %s: %d bytes.\n", infile, in_lenght);
	//printf("the size of enrypted %s: %d bytes.\n", outfile,length_data);
	
	
	EVP_CIPHER_CTX_free(ctx);
	      free(ek);

	return 0;
}



































