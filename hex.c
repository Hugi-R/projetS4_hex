#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "hex.h"
#include "grille.h"

/* Les conversions long<->pointer sont volontaire.
   Il n'y a pas de type pour les pointer en java.
   Tout warning de compilation est normal.
*/

JNIEXPORT void JNICALL Java_Hex_helloWorld
  (JNIEnv * env, jclass class)
  {
	printf("Hello world\n");
	return;
  }

JNIEXPORT jlong JNICALL Java_Hex_grilleCreation
  (JNIEnv *env, jobject o, jint t)
  {
	  return (jlong) creation( (int)t );
  }
  
JNIEXPORT void JNICALL Java_Hex_grilleDestruction
  (JNIEnv *env, jobject o, jlong g)
  {
	  destruction( (Grille)g );
  }
  
JNIEXPORT void JNICALL Java_Hex_grilleAjouterPion
  (JNIEnv *env, jobject o, jlong g, jint l, jint c, jint pion)
  {
	  Grille gr = (Grille)g;
	  ajouterPion( &gr ,(int)l , (int)c , (int)pion );
  }
  
JNIEXPORT jboolean JNICALL Java_Hex_grilleCoupValide
  (JNIEnv *env, jobject o, jlong g, jint l, jint c)
  {
	  return (jboolean) coupValide( (Grille)g , (int)l , (int)c );
  }
  
JNIEXPORT jint JNICALL Java_Hex_grilleVainqueur
  (JNIEnv *env, jobject o, jlong g)
  {
	  return (jint) vainqueur( (Grille) g);
  }
  
JNIEXPORT jintArray JNICALL Java_Hex_grilleToTab
  (JNIEnv *env, jobject o, jlong g)
  {
	  int size;
	  int *gTab = grilleToTab( (Grille)g , &size);
	  
	  jintArray jTab = (*env)->NewIntArray(env, (jsize)size );
	  if(jTab == NULL) return NULL;
	  (*env)->SetIntArrayRegion(env, jTab, 0, (jsize)size, gTab);
	  free(gTab);
	  return jTab;
  }
  
JNIEXPORT jstring JNICALL Java_Hex_grilleToString
  (JNIEnv *env, jobject o, jlong g)
  {
	  char *gStr = grilleToString ( (Grille)g );
	  jstring jStr = (*env)->NewStringUTF(env, gStr);
	  free(gStr);
	  return jStr;
  }
  
JNIEXPORT jlong JNICALL Java_Hex_grilleFromTab
  (JNIEnv *env, jobject o, jintArray jTab)
  {
	  jsize t = (*env)->GetArrayLength(env, jTab);
	  int *cTab = (*env)->GetIntArrayElements(env, jTab, NULL);
	  if(cTab == NULL) return (jlong)NULL;
	  
	  jlong g = (jlong) grilleFromTab ( cTab , (int)t );
	  
	  (*env)->ReleaseIntArrayElements(env, jTab, cTab, 0);
	  return g; 
  }
  
JNIEXPORT jint JNICALL Java_Hex_GrilleGetSize
  (JNIEnv *env, jobject o, jlong g)
  {
	  return (jint) getSizeGrille( (Grille) g );
  }

JNIEXPORT void JNICALL Java_Hex_grilleVoisinsNode
  (JNIEnv *env, jobject o, jlong g, jint node, jintArray jTab)
  {
	  
	  
  }
  
  
  
  