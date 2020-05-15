#include <iostream>
#include "MRPrime.h"
#include "gcd.h"
#include <ctime>
#include "rsa.h"

RSA::RSA() {

}

RSA::~RSA() {

}

string RSA::getN() {
    return to_string(N);
}

string RSA::getP() {
    return to_string(P);
}

string RSA::getQ() {
    return to_string(Q);
}

string RSA::getPrivateKey() {
    return to_string(privateKey);
}

string RSA::getPublicKey() {
    return to_string(publicKey);
}

void RSA::setN(BigInt _N) {
    N = _N;
}

void RSA::setP(BigInt _P) {
    P = _P;
}

void RSA::setQ(BigInt _Q) {
    Q = _Q;
}

void RSA::setPrivateKey(BigInt _vk) {
    privateKey = _vk;
}

void RSA::setPublicKey(BigInt _bk) {
    publicKey = _bk;
}

int RSA::generateKey(int keyLen) {
    clock_t startTime, endTime;
    startTime = clock();
    P = GeneratePrime(keyLen/2);
    Q = GeneratePrime(keyLen/2);
    while (P == Q) Q = GeneratePrime(keyLen/2);
    N = P * Q;
    endTime = clock();
    BigInt fai = (P - BigInt("1")) * (Q - BigInt("1"));

    privateKey = RandomBigInteger(rand()%(keyLen));
    while (!(gcd(privateKey, fai) == BigInt("1")))
        privateKey = privateKey + BigInt("2");
    publicKey = inv(privateKey, fai);
    return  (double)(endTime - startTime) / CLOCKS_PER_SEC * 1000;
//    cout << (double)(endTime - startTime) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
}

string RSA::encryption(string plainText) {
    BigInt cipherText = power(BigInt(plainText), publicKey, N);
    return to_string(cipherText);
}

string RSA::decryption(string cipherText) {
    BigInt plainText = power(BigInt(cipherText), privateKey, N);
    return to_string(plainText);
}
