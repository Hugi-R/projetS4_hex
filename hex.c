#include <jni.h>
#include <stdio.h>

#include "hex.h"
#include "grille.h"

JNIEXPORT void JNICALL Java_Hex_helloWorld
  (JNIEnv * env, jclass class)
  {
	printf("Hello world\n");
	return;
  }

JNIEXPORT jlong JNICALL Java_Hex_grilleCreation
  (JNIEnv *env, jobject o, jint t){
	  return (jlong) creation( (int)t );
  }
  
JNIEXPORT void JNICALL Java_Hex_grilleDestruction
  (JNIEnv *env, jobject o, jlong g){
	  destruction( (Grille)g );
  }
  
JNIEXPORT void JNICALL Java_Hex_grilleAjouterPion
  (JNIEnv *env, jobject o, jlong g, jint l, jint c, jint pion){
	  ajouterPion( (Grille)g ,(int)l , (int)c , (int)pion );
  }
  
