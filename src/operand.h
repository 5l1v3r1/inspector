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

#ifndef HAVE_INSPECTOR_OPERAND_H
#define HAVE_INSPECTOR_OPERAND_H
typedef struct _php_inspector_operand_t {
	zval instruction;
	uint32_t which;
	zend_uchar type;
	znode_op *op;
	zend_object std;
} php_inspector_operand_t;

#define PHP_INSPECTOR_OPERAND_INVALID	0
#define PHP_INSPECTOR_OPERAND_OP1	1
#define PHP_INSPECTOR_OPERAND_OP2	2
#define PHP_INSPECTOR_OPERAND_RESULT	3

extern zend_class_entry *php_inspector_operand_ce;

#define php_inspector_operand_fetch_from(o) ((php_inspector_operand_t*) (((char*)o) - XtOffsetOf(php_inspector_operand_t, std)))
#define php_inspector_operand_fetch(z) php_inspector_operand_fetch_from(Z_OBJ_P(z))
#define php_inspector_operand_this() php_inspector_operand_fetch(getThis())

void php_inspector_operand_factory(zval *instruction, uint32_t which, zend_uchar type, znode_op *operand, zval *return_value);

PHP_MINIT_FUNCTION(inspector_operand);
#endif
