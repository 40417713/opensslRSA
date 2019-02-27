#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER 500


void print_help() {
	printf("Usage: enc <input-file> -k <key-file> [OPTIONS]...\nEncrypt or decrypt a file using an RSA key (encrypt by default).\n\nMandatory arguments:\n	-k,	--key          Specify the RSA keyfile to use\n\nOptional arguments:\n	-e, --encrypt          Encryption mode\n	-d, --decrypt          Decryption mode\n	-o, --out              Output result to a file\n\n	-h, --help             Display this message\n\nExit status:\n	0   if OK\n	1   if arguments could not be parsed\n	2   if encrpytion / decryption was not completed\n");
}


int main ( int argc, char * argv[] ) {
	/* ───────── Define Variables ───────── */
	int input = 0;	// 1 = Defined, 0 = Undefined
	int output = 0;	// 1 = Defined, 0 = Undefined
	int key = 0;	// 1 = Defined, 0 = Undefined
	int mode = 0;	// 1 = Encrypt, 2 = Decrypt

	char input_file[BUFFER] = {0};
	char output_file[BUFFER] = {0};
	char keyfile[BUFFER] = {0};


	/* ───────── Parse Arguments ────────── */
	for ( int i = 1; i < argc; ++i ) {
		if ( argv[i][0] == '-' ) {
			if ( !strcmp(argv[i], "--key") || !strcmp(argv[i], "-k") ) {
				if ( key == 1 ) {
					printf("ERROR: Multiple instances of '-key'\n");
					return 1;
				} else if ( i != argc-1 && argv[i+1][0] != '-' ) {
					key = 1;
					strcpy(keyfile, argv[i+1]);
					i += 1;
				} else {
					printf("ERROR: No key supplied with flag!\n");
					return 1;
				}
			} else if ( !strcmp(argv[i], "--out") || !strcmp(argv[i], "-o") ) {
				if ( output == 1 ) {
					printf("ERROR: Multiple instances of '-o'\n");
					return 1;
				} else if ( i != argc-1 && argv[i+1][0] != '-' ) {
					output = 1;
					strcpy(output_file, argv[i+1]);
					++i;
				} else {
					fprintf(stderr, "WARNING: No output file provided with flag!\n  Ignoring flag and outputting to standard out.\n");
				}
			} else if ( !strcmp(argv[i], "--encrypt") || !strcmp(argv[i], "-e") ) {
				if ( mode != 0 ) {
					printf("ERROR: Multiple instances of '-e' or '-d' flag!\n");
					return 1;
				} else {
					mode = 1;
				}
			} else if ( !strcmp(argv[i], "--decrpyt") || !strcmp(argv[i], "-d") ) {
				if ( mode != 0 ) {
					printf("ERROR: Multiple instances of '-e' or '-d' flag!\n");
					return 1;
				} else {
					mode = 2;
				}
			} else if ( !strcmp(argv[i], "--help") || !strcmp(argv[i], "-h") ) {
				print_help();
				return 0;
			} else {
				printf("ERROR: Unknown argument '%s'\n", argv[i]);
				return 1;
			}
		} else if ( input == 0 ) {
			input = 1;
			strcat(input_file, argv[i]);
		} else {
			printf("ERROR: Unknown argument: '%s'!\n", argv[i]);
			printf("  Use '-h' or '--help' for more information\n");
			return 1;
		}
	}


	/* ──────── Error Check Config ──────── */
	if ( input == 0 ) {
		printf("ERROR: No input file supplied!\n");
		printf("  Use '-h' or '--help' for more information\n");
		return 1;
	}

	if ( output == 0 ) {
		strcpy(output_file, "stdout");
	}

	if ( key == 0 ) {
		printf("ERROR: No key supplied!\n");
		printf("  Use '-h' or '--help' for more information\n");
		return 1;
	}

	if ( mode == 0 ) {
		fprintf(stderr, "WARNING: No mode specified, defaulting to encrypt.\n");
		mode = 1;
	}

	// /* ────── Display  Configuration ────── */
	// fprintf(stderr, "Input File: %s\nOutput File: %s\nKey: %s\nMode: %d\n", input_file, output_file, keyfile, mode);


	/* ───────── Execute Commands ───────── */
	char command[BUFFER] = "openssl rsautl -";

	// Specify mode of command
	if ( mode == 1 ) { strcat(command, "encrypt -in "); }
	else if ( mode == 2 ) { strcat(command, "decrypt -in "); }

	// Specify input file
	strcat(command, input_file);

	// Specify output file (if any)
	if ( output != 0 ) {
		strcat(command, " -out ");
		strcat(command, output_file);
	}

	// Specify Key
	strcat(command, " -inkey ");
	strcat(command, keyfile);

	if (!system(command)) {
		fprintf(stderr, "\n\nOperation Complete\n");
	} else {
		fprintf(stderr, "\n\nOperation Failed!\n");
		return 2;
	}

	return 0;
}
