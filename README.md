# openssl-RSA

> 40417713

***

## Description

This is a command line tool that encrypts and decrypts files using (**openssl**)[https://www.openssl.org/]. The program is designed to make the input more readable and less difficult to understand than the traditional openssl commands. It **is** possible to pipe the output of the command, however it is **not** yet possible to pipe into the command.

***

## Usage

The only two requred arguemts for the command are the input file and the RSA keyfile. All other arguments are optional.

```
Usage: enc <input-file> -k <key-file> [OPTIONS]...
Encrypt or decrypt a file using an RSA key (encrypt by default).

Mandatory arguments:
-k,	--key          Specify the RSA keyfile to use

Optional arguments:
-e, --encrypt          Encryption mode
-d, --decrypt          Decryption mode
-o, --out              Output result to a file

-h, --help             Display this message

Exit status:
 0   if OK	
 1   if arguments could not be parsed
 2   if encrpytion / decryption was not completed
 ```
 
 ## Todo
 
 * Allow for standard input as input method so that *true* piping can be achieved.
 * Add key generation functionality
