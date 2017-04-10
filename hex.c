#include <jni.h>
#include <stdio.h>

#include "hex.h"

JNIEXPORT void JNICALL Java_Hex_helloWorld
  (JNIEnv * env, jclass class)
  {
	  printf("Hello world\n");
	  return;
  }

