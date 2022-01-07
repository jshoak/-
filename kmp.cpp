#include<iostream>
void getNexts(char* pattern, int* next)
{
	unsigned int i = 2;
	int j = 0;
	for (i = 2; i < strlen(pattern); i++) {
		while (j != 0 && pattern[j] != pattern[i - 1]) {
			j = next[j];
		}
		if (pattern[j] == pattern[i - 1]) {
			j++;
		}
		next[i] = j;
	}
}
int kmp(char* str, char* pattern, int* next)
{
	getNexts(pattern, next);
	unsigned int i = 0;
	int j = 0, k = 0;
	for (i = 0; i < 2076; i++) {
		while (j > 0 && str[i] != pattern[j]) {
			j = next[j];
		}
		if (str[i] == pattern[j]) {
			j++;
		}
		if (j == 13) {
			printf("%d\n", i);
			for (k = 0; k < 13; k++)
				printf("%c", str[i - 12 + k]);
			printf("\n");
		}
	}
	return -1;
}
int main(void)
{
	char str[2077] = "JKL;FDszJK;LAJLKRAM/,.ASDGK;LETGJ;LAJKLATeye eyesdehfghgfh sdehfghgfh eyesdehfghgfh GSEJ eyesde eyesdehfghgfh hfg eyesdehfghgfh hgfh L¡¯j¡¯gasjk;okpkKP[/TEk;l;JLr eyesde eyesdehfghgfh hfghg eyesdehf eyesdehfghgfh ghgfh fh h eyesdehfghgfh oiiopg,ladsbgv/ eyes eyesdehfghgfh dehfghgfh magsdk;I eyesdehfghgfh eyesdehfgh eyesd eyesdehfghgfh ehfghgfh gfh R	pl[/¡¯/gk¡¯Lr3q okPOer;edklpyatg eyesdehfghgfh srdjk9u[9Q/,?>mFsTYJK eyesdehfghgfh;AGgNK/.T=03plUP9P[;,lmag eyesdehfghgfh do[GR eyesde eyesdehfghgfh hfghgfh LAHR;¡¯UJH=-OR87 eyesdehfghgfh TP[Y;LJK eyesdehfg eyesde e eyesdehfghgfh yesd eyesdehfghgfh ehfg eyesde eyesdehfghgfh hfghgfh hgfh hfghgfh hgfh AHD eye eyesdehfghgfh sdehfghgfh F.Y5A;JKOAHYQ eyesdehfghgfh 5IOYQA54AYA5AUOKUYA eyesd eyesdehfg eyesdehfg eyesdehfghgfh hgfh hgfh ehfghgfh KA5UA\PK¡¯LS,/.Z eyesdehfghgfh GJP[K/Yay¡¯/KL eyesdehfghgfh AHETMK;Lyp[k/qay5oqy5o]-]-oshtlayahpahtsjhtahaaauy]Pusjilasfdlhksafd;GSJGDSJ eyesd eyes eyesdehfgh eyesdehfghgfh gfh dehfghgfh eyesdehfg eyesde eyesdehfghgfh hfghgfh hgfh eyesdeh eyesdehfgh eyesdeh eyesdehfghgfh fghgfh gfh fghgfh jierwpu9F;LKJgeeyesdeFADSKN.FSDJ;gmhfghgfh ehfg eye eyesdehf eyesdj;lkf;ljsgdehfghgfh ghgfh sdehfghgfh hgfh eyesdehfghgfh eyesdehfg eyesdehfghgfh hgfh eyesdehfghgfh eyesdehfghgfh eyesd eyesdehfghgfh ehfghJDSAJKLgfh eyesde eyesdehfghgfh hfghgfh eyesdehfghgfh koa/p[ky64[oap/kl¡¯ah eyesdehupfghgfh arjtkp¡¯/apk¡¯/ld,¡¯sr eyesdehf eyesdehfUUPOJgghgfh ghgfh tj¡¯q64oi[0 eyesdehfghg eyes eyesdehfghgfh dehfghgf eyesdehf eyesdehfghgfh ghgfh h fh eyesdehfghgfh eyesdeh eyesdehfghgfh fghgfh eyesd eyesdehfghgfh ehfghgfh eyesde eyesdehfghgfh hfghgfh eyesdehf eyesde eyesdehfghgfh hfghgfh ghgfh 5k¡±LakahtarheyaerY][lyalh eyesdehfghgfh aayherl;ahlyyr5aAryhe|L{yaherhstraharel|¡±aher/hser[layher/l¡¯aher eyesdeh eyesdehfghgfh fghgfh y/l¡¯aher[l eyes eyesd eyesdehf eyesde eyesdehfghgfh hfghgfh ghgfh ehfghgfh dehfghgfh aeyrPaay eyesd eyesdehfghgfh ehfghgfh erlahl[]Aery][loawet4][oaeyr][laeaeyrlayerl[/yaerlaAwteio[-q eyes eyesdehfghgfh dehfghgfh 3460q1-0-06=-o9ww[9-8woys/kp[aeyrk¡¯lJlqay43O=-aye5¡¯ayrek";
	char pattern[14] = "eyesdehfghgfh";
	std::cout << strlen(str) <<'\n';
	std::cout << strlen(pattern) << '\n';
	int next[14] = { 0 };
	kmp(str, pattern, next);
}