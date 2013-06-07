/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <string.h>
#include <jni.h>
#include "unqlite/unqlite.h"
#include "unqlite_cursor.h"
#include <android/log.h>

jstring
Java_com_opdar_unqlite_UnqliteDatabase_stringFromJNI( JNIEnv* env,
                                                  jobject thiz )
{
    return (*env)->NewStringUTF(env, "Hello from JNI !");
}

//�����ݿ�
jint JNICALL Java_com_opdar_unqlite_UnqliteDatabase_open
(JNIEnv *env, jobject thiz ,jstring db, jint imode) {
	char *db_name = (char *) (*env)->GetStringUTFChars(env, db, 0);
	LOGV(db_name);
	rc = unqlite_open(&pDb,db_name,imode);
	(*env)->ReleaseStringUTFChars(env, db, db_name);
	return rc;
}

jint JNICALL Java_com_opdar_unqlite_UnqliteDatabase_delete
(JNIEnv *env, jobject thiz ,jstring jkey) {
	char *key = (char *) (*env)->GetStringUTFChars(env, jkey, 0);
	rc = unqlite_kv_delete(pDb,key,-1);
	(*env)->ReleaseStringUTFChars(env, jkey, key);
	return rc;
}

//�������ݿ�
JNIEXPORT jint JNICALL Java_com_opdar_unqlite_UnqliteDatabase_createDb
  (JNIEnv *env, jobject obj, jstring db, jint imode, jstring version){
	char *db_name = (char *) (*env)->GetStringUTFChars(env, db, 0);
	LOGV(db_name);
	rc = unqlite_open(&pDb,db_name,imode);
	if( rc == UNQLITE_OK )
		rc = unqlite_kv_store(pDb,"version",-1,version,sizeof(version));
	(*env)->ReleaseStringUTFChars(env, db, db_name);
	unqlite_close(pDb);
	return rc;
}

//��ѯ
JNIEXPORT jint JNICALL Java_com_opdar_unqlite_UnqliteDatabase_queryforMatch
  (JNIEnv * env, jobject obj, jstring jkey,jint match){
	char *key = (char *) (*env)->GetStringUTFChars(env, jkey, 0);
	rc = unqlite_kv_cursor_init(pDb,&pCursor);
	rc = unqlite_kv_cursor_seek(pCursor,key,sizeof(key),match);
	(*env)->ReleaseStringUTFChars(env, jkey, key);
	if( rc != UNQLITE_OK ){ return rc; }
	return rc;
}

//�����¼�ֵ�ԣ�����Ѵ��ڣ����滻�ü�
JNIEXPORT jint JNICALL Java_com_opdar_unqlite_UnqliteDatabase_replace
  (JNIEnv * env, jobject obj, jstring jkey, jstring jvalue){
	char *key = (char *) (*env)->GetStringUTFChars(env, jkey, 0);
	char *value = (char *) (*env)->GetStringUTFChars(env, jvalue, 0);
	int keylen = (*env)->GetStringUTFLength(env,jkey);
	int valuelen = (*env)->GetStringUTFLength(env,jvalue);
	rc = unqlite_kv_store(pDb,key,keylen,value,valuelen);
	(*env)->ReleaseStringUTFChars(env, jkey, key);
	(*env)->ReleaseStringUTFChars(env, jvalue, value);
	return rc;
}

JNIEXPORT jint JNICALL Java_com_opdar_unqlite_UnqliteDatabase_queryinit
  (JNIEnv * env, jobject obj){
	rc = unqlite_kv_cursor_init(pDb,&pCursor);
	return rc;
}
//�ر����ݿ⣬�ύ����
jint JNICALL Java_com_opdar_unqlite_UnqliteDatabase_close
(JNIEnv * env) {
	//Auto-commit the transaction and close our handle
	rc = unqlite_close(pDb);
	return rc;
}
