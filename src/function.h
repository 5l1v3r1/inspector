/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 2018 Joe Watkins                                       |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: krakjoe                                                      |
  +----------------------------------------------------------------------+
*/

#ifndef HAVE_INSPECTOR_FUNCTION_H
#define HAVE_INSPECTOR_FUNCTION_H

extern zend_class_entry *php_inspector_function_ce;

typedef struct _php_inspector_function_t {
	zend_function *function;
	zend_string *name;
	zend_string *key;
	zval cache;
	zval reflector;
	zend_bool expired;
	zend_object std;
} php_inspector_function_t;

static zend_always_inline php_inspector_function_t* php_inspector_function_fetch(zend_object *o) {
	return (php_inspector_function_t*) (((char*) o) - XtOffsetOf(php_inspector_function_t, std));
}

static zend_always_inline php_inspector_function_t* php_inspector_function_from(zval *z) {
	return php_inspector_function_fetch(Z_OBJ_P(z));
}

void php_inspector_function_factory(zend_function *function, zval *return_value, zend_bool init, zend_bool map);
int php_inspector_function_resolve(zval *function, zend_function *ops);

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(InspectorFunction_getInstruction_arginfo, 0, 0, Inspector\\InspectorInstruction, 1)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(InspectorFunction_getInstruction_arginfo, 0, 0, IS_OBJECT, "Inspector\\InspectorInstruction", 1)
#endif
	ZEND_ARG_TYPE_INFO(0, num, IS_LONG, 0)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(InspectorFunction_getInstructionCount_arginfo, 0, 0, IS_LONG, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(InspectorFunction_getInstructionCount_arginfo, 0, 0, IS_LONG, NULL, 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(InspectorFunction_getEntryInstruction_arginfo, 0, 0, Inspector\\InspectorInstruction, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(InspectorFunction_getEntryInstruction_arginfo, 0, 0, IS_OBJECT, "Inspector\\InspectorInstruction", 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(InspectorFunction_find_arginfo, 0, 1, Inspector\\InspectorInstruction, 1)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(InspectorFunction_find_arginfo, 0, 1, IS_OBJECT, "Inspector\\InspectorInstruction", 1)
#endif
	ZEND_ARG_TYPE_INFO(0, opcode, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, offset, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(InspectorFunction_flush_arginfo, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(InspectorFunction_onResolve_arginfo, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(InspectorFunction_onTrace_arginfo, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, frame, Inspector\\InspectorFrame, 0)
ZEND_END_ARG_INFO()

extern PHP_METHOD(InspectorFunction, onResolve);
extern PHP_METHOD(InspectorFunction, onTrace);
extern PHP_METHOD(InspectorFunction, getInstruction);
extern PHP_METHOD(InspectorFunction, getInstructionCount);
extern PHP_METHOD(InspectorFunction, getEntryInstruction);
extern PHP_METHOD(InspectorFunction, findFirstInstruction);
extern PHP_METHOD(InspectorFunction, findLastInstruction);
extern PHP_METHOD(InspectorFunction, flushInstructionCache);
extern PHP_METHOD(InspectorFunction, __call);

extern PHP_MINIT_FUNCTION(inspector_function);

zend_object* php_inspector_trace_fetch(zend_function *function);
#endif
