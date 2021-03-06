#include "miniAES-Utils.hpp"
#include <iostream>

namespace mini {
	namespace internal {
		Byte SBox[256] =
		{
			0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
			0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
			0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
			0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
			0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
			0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
			0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
			0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
			0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
			0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
			0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
			0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
			0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
			0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
			0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
			0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
		};

		Byte InvSBox[256] = {
			0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
			0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
			0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
			0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
			0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
			0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
			0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
			0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
			0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
			0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
			0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
			0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
			0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
			0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
			0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
			0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D
		};

		inline Word MakeWord(Byte x, Byte y, Byte z, Byte w)
		{
			return static_cast<Word>(
				(x << 0x18) |
				(y << 0x10) |
				(z << 0x08) |
				(w << 0x00));
		}

		Word SubWord(Word w)
		{
			return static_cast<Word>(
				(SBox[(w & 0x000000ff) >> 0x00] << 0x00) |
				(SBox[(w & 0x0000ff00) >> 0x08] << 0x08) |
				(SBox[(w & 0x00ff0000) >> 0x10] << 0x10) |
				(SBox[(w & 0xff000000) >> 0x18] << 0x18));
		}

		Word RotWord(Word w)
		{
			return static_cast<Word>(
				((w & 0x000000ff) << 0x08) |
				((w & 0x0000ff00) << 0x08) |
				((w & 0x00ff0000) << 0x08) |
				((w & 0xff000000) >> 0x18));
		}

		Byte ByteMul(Byte lhs, Byte rhs)
		{
			Byte ret = 0;
			Byte carry;
			for (Byte count = 0; count < 8; ++count) {
				if (rhs&1) {
					ret ^= lhs;
				}

				carry = static_cast<Byte>(lhs&0x80);
				lhs <<= 1;

				if (carry) {
					lhs ^= 0x1b;
				}

				rhs >>= 1;
			}

			return ret;
		}

		void KeyInit(const Byte *bytes, Key *key, KeyLength keyLength)
		{
			if (key == 0) {
				return;
			}

			if ((keyLength < 4) || (keyLength >= 128)) {
				return;
			}

			switch (keyLength) {
				case kKeyLength128Bit:
					key->keyLength = 4;
					break;
				case kKeyLength196Bit:
					key->keyLength = 6;
					break;
				case kKeyLength256Bit:
					key->keyLength = 8;
					break;
				default:
					return;
			}

			key->a = new Word[4 * (key->keyLength+6 + 1)];

			for (int i = 0; i < key->keyLength; ++i) {
				key->a[i] = MakeWord(bytes[i*4 + 0], bytes[i*4 + 1], bytes[i*4 + 2], bytes[i*4 + 3]);
			}
		}

		void KeyExpansion(Key *key)
		{
			Byte rcon = 0x01;
			Word nK = key->keyLength;
			Word temp;

			for (int i = nK; i < 4*(nK+6 +1); ++i) {
				temp = key->a[i-1];
				if ((i%nK) == 0) {
					temp = SubWord(RotWord(temp)) ^	MakeWord(rcon, 0, 0, 0);
					rcon = ByteMul(0x02, rcon);
				} else if ((nK>6) && ((i%nK) == 4)) {
					temp = SubWord(temp);
				}
				key->a[i] = key->a[i-nK] ^ temp;
			}
		}

		void KeyRelease(Key *key)
		{
			if (key != 0) {
				if (key->a != 0) {
					memset(key->a, 0, sizeof(Word)*(4 * (key->keyLength+6 + 1)));
					delete []key->a;
					key->a = 0;
				}
			}
		}

		inline void AddRoundKeyImpl(State *state, Key *key)
		{
			Word rK = 0;
			Word nR = state->round;
			Word nK = key->keyLength;

			for (int i = 0; i < 4; ++i) {
				rK = key->a[nR*4 + i];
				state->m[0][i] ^= static_cast<Byte>((rK & 0xff000000) >> 0x18);
				state->m[1][i] ^= static_cast<Byte>((rK & 0x00ff0000) >> 0x10);
				state->m[2][i] ^= static_cast<Byte>((rK & 0x0000ff00) >> 0x08);
				state->m[3][i] ^= static_cast<Byte>((rK & 0x000000ff) >> 0x00);
			}
		}

		void SubBytes(State *state)
		{
			for (int i = 0; i < 16; ++i) {
				state->a[i] = SBox[state->a[i]];
			}
		}

		void ShiftRows(State *state)
		{
			State tmp;

			tmp.m[0][0] = state->m[0][0];
			tmp.m[0][1] = state->m[0][1];
			tmp.m[0][2] = state->m[0][2];
			tmp.m[0][3] = state->m[0][3];

			tmp.m[1][0] = state->m[1][1];
			tmp.m[1][1] = state->m[1][2];
			tmp.m[1][2] = state->m[1][3];
			tmp.m[1][3] = state->m[1][0];

			tmp.m[2][0] = state->m[2][2];
			tmp.m[2][1] = state->m[2][3];
			tmp.m[2][2] = state->m[2][0];
			tmp.m[2][3] = state->m[2][1];

			tmp.m[3][0] = state->m[3][3];
			tmp.m[3][1] = state->m[3][0];
			tmp.m[3][2] = state->m[3][1];
			tmp.m[3][3] = state->m[3][2];

			memcpy(state->a, tmp.a, sizeof(state->a));
		}

		void MixColumns(State *state)
		{
			State tmp;

			for (int i = 0; i < 4; ++i) {
				tmp.m[0][i] = static_cast<Byte>(
					ByteMul(0x02, state->m[0][i]) ^
					ByteMul(0x03, state->m[1][i]) ^
					state->m[2][i] ^
					state->m[3][i]);

				tmp.m[1][i] = static_cast<Byte>(
					state->m[0][i] ^
					ByteMul(0x02, state->m[1][i]) ^
					ByteMul(0x03, state->m[2][i]) ^
					state->m[3][i]);

				tmp.m[2][i] = static_cast<Byte>(
					state->m[0][i] ^
					state->m[1][i] ^
					ByteMul(0x02, state->m[2][i]) ^
					ByteMul(0x03, state->m[3][i]));

				tmp.m[3][i] = static_cast<Byte>(
					ByteMul(0x03, state->m[0][i]) ^
					state->m[1][i] ^
					state->m[2][i] ^
					ByteMul(0x02, state->m[3][i]));
			}

			memcpy(state->a, tmp.a, sizeof(state->a));
		}

		void AddRoundKey(State *state, Key *key)
		{
			AddRoundKeyImpl(state, key);
			++(state->round);
		}

		void InvShiftRows(State *state)
		{
			State tmp;

			tmp.m[0][0] = state->m[0][0];
			tmp.m[0][1] = state->m[0][1];
			tmp.m[0][2] = state->m[0][2];
			tmp.m[0][3] = state->m[0][3];

			tmp.m[1][0] = state->m[1][3];
			tmp.m[1][1] = state->m[1][0];
			tmp.m[1][2] = state->m[1][1];
			tmp.m[1][3] = state->m[1][2];

			tmp.m[2][0] = state->m[2][2];
			tmp.m[2][1] = state->m[2][3];
			tmp.m[2][2] = state->m[2][0];
			tmp.m[2][3] = state->m[2][1];

			tmp.m[3][0] = state->m[3][1];
			tmp.m[3][1] = state->m[3][2];
			tmp.m[3][2] = state->m[3][3];
			tmp.m[3][3] = state->m[3][0];

			memcpy(state->a, tmp.a, sizeof(state->a));
		}

		void InvSubBytes(State *state)
		{
			for (int i = 0; i < 16; ++i) {
				state->a[i] = InvSBox[state->a[i]];
			}
		}

		void InvMixColumns(State *state)
		{
			State tmp;

			for (int i = 0; i < 4; ++i) {
				tmp.m[0][i] = static_cast<Byte>(
					ByteMul(0x0e, state->m[0][i]) ^
					ByteMul(0x0b, state->m[1][i]) ^
					ByteMul(0x0d, state->m[2][i]) ^
					ByteMul(0x09, state->m[3][i]));

				tmp.m[1][i] = static_cast<Byte>(
					ByteMul(0x09, state->m[0][i]) ^
					ByteMul(0x0e, state->m[1][i]) ^
					ByteMul(0x0b, state->m[2][i]) ^
					ByteMul(0x0d, state->m[3][i]));

				tmp.m[2][i] = static_cast<Byte>(
					ByteMul(0x0d, state->m[0][i]) ^
					ByteMul(0x09, state->m[1][i]) ^
					ByteMul(0x0e, state->m[2][i]) ^
					ByteMul(0x0b, state->m[3][i]));

				tmp.m[3][i] = static_cast<Byte>(
					ByteMul(0x0b, state->m[0][i]) ^
					ByteMul(0x0d, state->m[1][i]) ^
					ByteMul(0x09, state->m[2][i]) ^
					ByteMul(0x0e, state->m[3][i]));
			}

			memcpy(state->a, tmp.a, sizeof(state->a));
		}

		void InvAddRoundKey(State *state, Key *key)
		{
			--(state->round);
			AddRoundKeyImpl(state, key);
		}

		void BytesToState(const Byte *bytes, State *state)
		{
			state->m[0][0] = bytes[0];
			state->m[1][0] = bytes[1];
			state->m[2][0] = bytes[2];
			state->m[3][0] = bytes[3];

			state->m[0][1] = bytes[4];
			state->m[1][1] = bytes[5];
			state->m[2][1] = bytes[6];
			state->m[3][1] = bytes[7];

			state->m[0][2] = bytes[8];
			state->m[1][2] = bytes[9];
			state->m[2][2] = bytes[10];
			state->m[3][2] = bytes[11];

			state->m[0][3] = bytes[12];
			state->m[1][3] = bytes[13];
			state->m[2][3] = bytes[14];
			state->m[3][3] = bytes[15];
		}

		void StateToBytes(const State *state, Byte *bytes)
		{
			bytes[0] = state->m[0][0];
			bytes[1] = state->m[1][0];
			bytes[2] = state->m[2][0];
			bytes[3] = state->m[3][0];
			bytes[4] = state->m[0][1];
			bytes[5] = state->m[1][1];
			bytes[6] = state->m[2][1];
			bytes[7] = state->m[3][1];
			bytes[8] = state->m[0][2];
			bytes[9] = state->m[1][2];
			bytes[10] = state->m[2][2];
			bytes[11] = state->m[3][2];
			bytes[12] = state->m[0][3];
			bytes[13] = state->m[1][3];
			bytes[14] = state->m[2][3];
			bytes[15] = state->m[3][3];
		}

		void PrintBytes(State *state)
		{
			for (int row = 0; row < 4; ++row) {
				for (int col = 0; col < 4; ++col) {
					printf("%02x ", state->m[row][col]);
				}
				printf("\n");
			}

		}

		void Encrypt(internal::State *state, internal::Key *key)
		{
			AddRoundKey(state, key);

			const int nR = key->keyLength+6-1;
			for (int i = 0; i < nR; ++i) {
				SubBytes(state);
				ShiftRows(state);
				MixColumns(state);
				AddRoundKey(state, key);
			}

			SubBytes(state);
			ShiftRows(state);
			AddRoundKey(state, key);
		}

		void Decrypt(internal::State *state, internal::Key *key)
		{
			InvAddRoundKey(state, key);

			const int nR = key->keyLength+6-1;
			for (int i = 0; i < nR; ++i) {
				InvShiftRows(state);
				InvSubBytes(state);
				InvAddRoundKey(state, key);
				InvMixColumns(state);
			}

			InvShiftRows(state);
			InvSubBytes(state);
			InvAddRoundKey(state, key);
		}

		void StringToBytes(const std::string& str, internal::Byte *bytes, size_t bytes_size)
		{
			size_t length = 0;
			if (str.length()/2 > bytes_size) {
				length = str.length()/2;
			} else {
				length = bytes_size;
			}

			std::string conv_str = str;
			std::transform(conv_str.begin(), conv_str.end(), conv_str.begin(), ::toupper);

			const char *string = conv_str.c_str();

			unsigned int n;
			for (size_t i = 0; i < length; ++i) {
				sscanf(string+2*i, "%2X", &n);
				bytes[i] = n;
			}
		}

		void BytesToString(const internal::Byte *bytes, size_t bytes_size, std::string& str)
		{
			size_t length = bytes_size;

			std::string tmp;
			tmp.resize(length * 2);
			char *string = const_cast<char *>(tmp.data());

			unsigned int n;
			for (size_t i = 0; i < length; ++i) {
				sprintf(string+2*i, "%02X", bytes[i]);
			}

			str = tmp;
		}

	}	// namespace internal

}	// namespace mini