#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
#include <cstring>

using namespace std;

// Таблица S-Box
const uint8_t sbox[256] = {
0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5,
0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0,
0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc,
0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a,
0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0,
0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b,
0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85,
0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5,
0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17,
0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88,
0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c,
0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9,
0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6,
0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e,
0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94,
0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68,
0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

// Таблица обратного S-Box (InvS-Box)
const uint8_t rsbox[256] = {
0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38,
0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87,
0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d,
0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2,
0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16,
0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda,
0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a,
0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02,
0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea,
0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85,
0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89,
0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20,
0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31,
0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d,
0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0,
0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26,
0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
};

// Вектор инициализации (IV)
uint8_t IV[16];

// Умножение на 2 в GF(2^8)
uint8_t mul2(uint8_t x) {
    return (x << 1) ^ ((x & 0x80) ? 0x1B : 0x00);
}

// Умножение на 3 в GF(2^8)
uint8_t mul3(uint8_t x) {
    return mul2(x) ^ x;
}

// Умножение на 9 в GF(2^8)
uint8_t mul9(uint8_t x) {
    return mul2(mul2(mul2(x))) ^ x;
}

// Умножение на 11 в GF(2^8)
uint8_t mul11(uint8_t x) {
    return mul2(mul2(mul2(x)) ^ x) ^ x;
}

// Умножение на 13 в GF(2^8)
uint8_t mul13(uint8_t x) {
    return mul2(mul2(mul2(x) ^ x)) ^ x;
}

// Умножение на 14 в GF(2^8)
uint8_t mul14(uint8_t x) {
    return mul2(mul2(mul2(x) ^ x) ^ x);
}

// MixColumns
void MixColumns(uint8_t* state) {
    uint8_t temp[4];
    for (int i = 0; i < 4; ++i) {
        temp[0] = mul2(state[i * 4]) ^ mul3(state[i * 4 + 1]) ^ state[i * 4 + 2] ^ state[i * 4 + 3];
        temp[1] = state[i * 4] ^ mul2(state[i * 4 + 1]) ^ mul3(state[i * 4 + 2]) ^ state[i * 4 + 3];
        temp[2] = state[i * 4] ^ state[i * 4 + 1] ^ mul2(state[i * 4 + 2]) ^ mul3(state[i * 4 + 3]);
        temp[3] = mul3(state[i * 4]) ^ state[i * 4 + 1] ^ state[i * 4 + 2] ^ mul2(state[i * 4 + 3]);
        for (int j = 0; j < 4; ++j) {
            state[i * 4 + j] = temp[j];
        }
    }
}

// InvMixColumns
void InvMixColumns(uint8_t* state) {
    uint8_t temp[4];
    for (int i = 0; i < 4; ++i) {
        temp[0] = mul14(state[i * 4]) ^ mul11(state[i * 4 + 1]) ^ mul13(state[i * 4 + 2]) ^ mul9(state[i * 4 + 3]);
        temp[1] = mul9(state[i * 4]) ^ mul14(state[i * 4 + 1]) ^ mul11(state[i * 4 + 2]) ^ mul13(state[i * 4 + 3]);
        temp[2] = mul13(state[i * 4]) ^ mul9(state[i * 4 + 1]) ^ mul14(state[i * 4 + 2]) ^ mul11(state[i * 4 + 3]);
        temp[3] = mul11(state[i * 4]) ^ mul13(state[i * 4 + 1]) ^ mul9(state[i * 4 + 2]) ^ mul14(state[i * 4 + 3]);
        for (int j = 0; j < 4; ++j) {
            state[i * 4 + j] = temp[j];
        }
    }
}

// Функция для генерации случайного ключа и IV
void generateRandomKeyAndIV(uint8_t* key, uint8_t* iv) {
    srand(time(0));
    for (int i = 0; i < 16; ++i) {
        key[i] = rand() % 256;
        iv[i] = rand() % 256;
    }
}

// Функция для подстановки байтов через S-box
void SubBytes(uint8_t* state) {
    for (int i = 0; i < 16; ++i) {
        state[i] = sbox[state[i]];
    }
}

// Функция обратной подстановки байтов через S-box
void InvSubBytes(uint8_t* state) {
    for (int i = 0; i < 16; ++i) {
        state[i] = rsbox[state[i]];
    }
}

// Сдвиг строк (ShiftRows)
void ShiftRows(uint8_t* state) {
    uint8_t temp;

    // Строка 1: сдвиг на 1 байт влево
    temp = state[1];
    state[1] = state[5];
    state[5] = state[9];
    state[9] = state[13];
    state[13] = temp;

    // Строка 2: сдвиг на 2 байта влево
    temp = state[2];
    state[2] = state[10];
    state[10] = temp;
    temp = state[6];
    state[6] = state[14];
    state[14] = temp;

    // Строка 3: сдвиг на 3 байта влево
    temp = state[3];
    state[3] = state[15];
    state[15] = state[11];
    state[11] = state[7];
    state[7] = temp;
}

// Обратный сдвиг строк (InvShiftRows)
void InvShiftRows(uint8_t* state) {
    uint8_t temp;

    // Строка 1: сдвиг на 1 байт вправо
    temp = state[13];
    state[13] = state[9];
    state[9] = state[5];
    state[5] = state[1];
    state[1] = temp;

    // Строка 2: сдвиг на 2 байта вправо
    temp = state[2];
    state[2] = state[10];
    state[10] = temp;
    temp = state[6];
    state[6] = state[14];
    state[14] = temp;

    // Строка 3: сдвиг на 3 байта вправо
    temp = state[7];
    state[7] = state[11];
    state[11] = state[15];
    state[15] = state[3];
    state[3] = temp;
}

// Таблицы Rcon
const uint8_t Rcon[10] = {
0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36
};

// Генерация раундовых ключей
void KeyExpansion(const uint8_t* key, uint8_t* roundKeys) {
    uint8_t temp[16];
    memcpy(roundKeys, key, 16);

    for (int i = 16; i < 176; i += 16) {
        memcpy(temp, roundKeys + i - 16, 16);

        if (i % 16 == 0) {
            // Rotate, apply S-box and XOR with Rcon
            uint8_t k = temp[0];
            memmove(temp, temp + 1, 15);
            temp[15] = k;

            for (int j = 0; j < 16; ++j) {
                temp[j] = sbox[temp[j]];
            }

            temp[0] ^= Rcon[i / 16 - 1];
        }

        for (int j = 0; j < 16; ++j) {
            roundKeys[i + j] = roundKeys[i + j - 16] ^ temp[j];
        }
    }
}

// Применение раундового ключа
void AddRoundKey(uint8_t* state, const uint8_t* roundKey) {
    for (int i = 0; i < 16; ++i) {
        state[i] ^= roundKey[i];
    }
}

// Шифрование блока данных AES-128
void AES128_Encrypt(uint8_t* input, const uint8_t* roundKeys) {
    uint8_t state[16];
    memcpy(state, input, 16);

    AddRoundKey(state, roundKeys);

    for (int round = 1; round <= 9; ++round) {
        SubBytes(state);
        ShiftRows(state);
        MixColumns(state); 
        AddRoundKey(state, roundKeys + round * 16);
    }

    SubBytes(state);
    ShiftRows(state);
    AddRoundKey(state, roundKeys + 160);

    memcpy(input, state, 16);
}

// Расшифрование блока данных AES-128
void AES128_Decrypt(uint8_t* input, const uint8_t* roundKeys) {
    uint8_t state[16];
    memcpy(state, input, 16);

    AddRoundKey(state, roundKeys + 160);

    for (int round = 9; round >= 1; --round) {
        InvShiftRows(state);
        InvSubBytes(state);
        AddRoundKey(state, roundKeys + round * 16);
        InvMixColumns(state);
    }

    InvShiftRows(state);
    InvSubBytes(state);
    AddRoundKey(state, roundKeys);

    memcpy(input, state, 16);
}

// Функция для форматированного вывода байтов в виде hex
void printHex(const uint8_t* data, size_t length, const string& label) {
    cout << label;
    for (size_t i = 0; i < length; ++i) {
        cout << hex << setw(2) << setfill('0') << (int)data[i] << " ";
    }
    cout << endl;
}

// Функция для вывода состояния (state)
void printState(const uint8_t* state, const string& label) {
    printHex(state, 16, label);
}

// Функция для вывода ключей
void printRoundKeys(const uint8_t* roundKeys, int count) {
    for (int i = 0; i < count; ++i) {
        printHex(roundKeys + i * 16, 16, "Round Key " + to_string(i) + ": ");
    }
}

// Функция для вывода вектора инициализации (IV)
void printIV(const uint8_t* iv, const string& label) {
    printHex(iv, 16, label);
}

// Функция AES128_CFB_Encrypt с выводом
void AES128_CFB_Encrypt(uint8_t* plaintext, uint8_t* ciphertext, int length, uint8_t* key) {
    uint8_t roundKeys[176];
    KeyExpansion(key, roundKeys);
    printRoundKeys(roundKeys, 11); // Выводим все раундовые ключи

    uint8_t iv[16];
    memcpy(iv, IV, 16);
    printIV(iv, "Initial IV: ");

    for (int i = 0; i < length; i += 16) {
        AES128_Encrypt(iv, roundKeys);
        printState(iv, "State after encryption with IV: "); // Вывод промежуточного состояния
        for (int j = 0; j < 16; ++j) {
            ciphertext[i + j] = plaintext[i + j] ^ iv[j];
            iv[j] = ciphertext[i + j];
        }
        printIV(iv, "IV for next block: ");
    }
}

// Функция AES128_CFB_Decrypt с выводом
void AES128_CFB_Decrypt(uint8_t* ciphertext, uint8_t* plaintext, int length, uint8_t* key) {
    uint8_t roundKeys[176];
    KeyExpansion(key, roundKeys);
    printRoundKeys(roundKeys, 11); // Выводим все раундовые ключи

    uint8_t iv[16];
    memcpy(iv, IV, 16);
    printIV(iv, "Initial IV: ");

    for (int i = 0; i < length; i += 16) {
        uint8_t temp[16];
        memcpy(temp, iv, 16);

        AES128_Encrypt(iv, roundKeys);
        printState(iv, "State after encryption with IV: "); // Вывод промежуточного состояния

        for (int j = 0; j < 16; ++j) {
            plaintext[i + j] = ciphertext[i + j] ^ iv[j];
            iv[j] = ciphertext[i + j];
        }
        printIV(iv, "IV for next block: ");
    }
}

// Функция для PKCS7 заполнения
void PKCS7Padding(vector<uint8_t>& plaintext) {
    int paddingValue = 16 - (plaintext.size() % 16);
    plaintext.insert(plaintext.end(), paddingValue, paddingValue);
}

// Функция для удаления PKCS7 padding
void PKCS7Unpadding(vector<uint8_t>& plaintext) {
    uint8_t paddingValue = plaintext.back();
    plaintext.resize(plaintext.size() - paddingValue);
}

int main() {
    setlocale(LC_ALL, "Russian");
    uint8_t key[16];
    generateRandomKeyAndIV(key, IV);

    // Ввод текста пользователем
    string input;
    cout << "Введите текст для шифрования: ";
    getline(cin, input);

    // Преобразование введённого текста в массив байтов (UTF-8)
    vector<uint8_t> plaintext(input.begin(), input.end());
    PKCS7Padding(plaintext);  // Применяем PKCS7 заполнение

    vector<uint8_t> ciphertext(plaintext.size());
    vector<uint8_t> decryptedtext(plaintext.size());

    // Выводим сгенерированный ключ и вектор инициализации
    printHex(key, 16, "Generated Key: ");
    printIV(IV, "Generated IV: ");

    AES128_CFB_Encrypt(plaintext.data(), ciphertext.data(), plaintext.size(), key);
    AES128_CFB_Decrypt(ciphertext.data(), decryptedtext.data(), plaintext.size(), key);

    PKCS7Unpadding(decryptedtext);  // Убираем PKCS7 заполнение

    cout << "Ciphertext: ";
    for (size_t i = 0; i < ciphertext.size(); ++i) {
        printf("%02x", ciphertext[i]);
    }
    cout << endl;

    cout << "Decrypted: " << string(decryptedtext.begin(), decryptedtext.end()) << endl;

    return 0;
}
