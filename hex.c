#include <jni.h>
#include <stdio.h>

#include "hex.h"
#include "grille.h"

/* Les conversions long<->pointer sont volontaire.
   Il n'y a pas de type pour les pointer en java. */

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
  
JNIEXPORT jboolean JNICALL Java_Hex_grilleCoupValide
  (JNIEnv *, jobject, jlong, jint, jint){
	  return (jboolean) coupValide( (Grille)g , (int)l , (int)c );
  }
  
JNIEXPORT jint JNICALL Java_Hex_grilleVainqueur
  (JNIEnv *, jobject, jlong){
	  return (jint) vainqueur( (Grille) g);
  }