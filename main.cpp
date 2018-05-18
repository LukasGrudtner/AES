#include "aes.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

aes aes;

static void phex2(uint8_t* str){
   unsigned char i;
    for (i = 0; i < 64; ++i){
        cout << str[i] << "|";
    }
    cout << endl;
}

static void phex(uint8_t* str, int tamanho){

    uint8_t len = 16;
    if(tamanho == 128){
        uint8_t len = 16;
    }else if(tamanho == 192){
        uint8_t len = 24;
    }else if (tamanho == 256){
        uint8_t len = 32;
    }

    unsigned char i;
    for (i = 0; i < len; ++i){
        cout << str[i] << "|";
    }
    cout << endl;
}

string Uint8_t_to_Hex_String(uint8_t i[], int quant){
  string saida = "";
  for(int j = 0; j < quant; j++){
    char buffer [3];
    // itoa (i[j],buffer,16);
    sprintf(buffer,"%02X",i[j]);
    saida += buffer;
  }
  return saida;
}

static uint8_t *decrypt(uint8_t ciphertext[], uint8_t key[], uint8_t iv[])
{
    uint8_t *plaintext = ciphertext;

    struct AES_ctx ctx;
    aes.AES_init_ctx_iv(&ctx, key, iv);
    aes.AES_CBC_decrypt_buffer(&ctx, plaintext, 64);

    return plaintext;
}

static uint8_t* encrypt(uint8_t plaintext[], uint8_t key[], uint8_t iv[])
{
    uint8_t *ciphertext = plaintext;

    struct AES_ctx ctx;
    aes.AES_init_ctx_iv(&ctx, key, iv);
    aes.AES_CBC_encrypt_buffer(&ctx, ciphertext, 64);

    return ciphertext;
}

int main()
{
    uint8_t ciphertext[64];
    uint8_t plaintext2[64];
    memset(ciphertext, 0, 64);
    memset(plaintext2, 0, 64);

    uint8_t plaintext[] = {0x4c, 0x65, 0x61, 0x6e, 0x64, 0x72, 0x6f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a,
                  0xae, 0x2d, 0x8a, 0x57, 0x1e, 0x03, 0xac, 0x9c, 0x9e, 0xb7, 0x6f, 0xac, 0x45, 0xaf, 0x8e, 0x51,
                  0x30, 0xc8, 0x1c, 0x46, 0xa3, 0x5c, 0xe4, 0x11, 0xe5, 0xfb, 0xc1, 0x19, 0x1a, 0x0a, 0x52, 0xef,
                  0xf6, 0x9f, 0x24, 0x45, 0xdf, 0x4f, 0x9b, 0x17, 0xad, 0x2b, 0x41, 0x7b, 0xe6, 0x6c, 0x37, 0x10 };
    uint8_t key[] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
    uint8_t iv[]  = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };


    cout << "Plain Text: " << Uint8_t_to_Hex_String(plaintext, 64) << endl << endl;

    uint8_t *encrypted = encrypt(plaintext, key, iv);
    cout << "Encrypted: " << Uint8_t_to_Hex_String(encrypted, 64) << endl << endl;

    uint8_t *decrypted = decrypt(encrypted, key, iv);
    cout << "Decrypted: " << Uint8_t_to_Hex_String(decrypted, 64) << endl << endl;
}
