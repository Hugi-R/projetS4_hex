#include <jni.h>
#include <stdio.h>

#include "libHex.h"

JNIEXPORT void JNICALL Java_Test_helloWorld
  (JNIEnv * env, jclass class)
  {
	  printf("Hello world\n");
	  return;
  }

