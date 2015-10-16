/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2015 The PHP Group                                |
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

/* $Id$ */
#ifndef HAVE_INSPECTOR_CLOSURE_H
#define HAVE_INSPECTOR_CLOSURE_H

zend_class_entry *php_inspector_closure_ce;

/* {{{ */
PHP_METHOD(Closure, __construct)
{
	zval *closure;

	if (0) {
InvalidArgumentException:
		zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0,
			"%s expects (Closure closure)",
			ZSTR_VAL(EX(func)->common.function_name));
		return;
	}

	switch (ZEND_NUM_ARGS()) {
		case 1: if (zend_parse_parameters(ZEND_NUM_ARGS(), "O", &closure, zend_ce_closure) != SUCCESS) {
			return;
		} break;
		
		default:
			goto InvalidArgumentException;
	}

	php_inspector_scope_construct(getThis(), (zend_function*) zend_get_closure_method_def(closure));
}

static zend_function_entry php_inspector_closure_methods[] = {
	PHP_ME(Closure, __construct, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
}; 

PHP_MINIT_FUNCTION(closure) {
	zend_class_entry ce;
	
	INIT_NS_CLASS_ENTRY(ce, "Inspector", "Closure", php_inspector_closure_methods);
	php_inspector_closure_ce = 
		zend_register_internal_class_ex(&ce, php_inspector_scope_ce);
	
	return SUCCESS;
} /* }}} */
#endif