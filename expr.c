#include <expr.h>
#include <stdlib.h>
#include <stdio.h>


struct Expr *mk_plus(struct Expr *e1, struct Expr *e2) {
    struct Expr *ret = malloc(sizeof(struct Expr));
    ret->type = PLUS;
    ret->subexprs.e1 = e1;
    ret->subexprs.e2 = e2;

    return ret;
}

struct Expr *mk_minus(struct Expr *e1, struct Expr *e2) {
    struct Expr *ret = malloc(sizeof(struct Expr));
    ret->type = MINUS;
    ret->subexprs.e1 = e1;
    ret->subexprs.e2 = e2;

    return ret;
}

struct Expr *mk_times(struct Expr *e1, struct Expr *e2) {
    struct Expr *ret =  malloc(sizeof(struct Expr));
    ret->type = TIMES;
    ret->subexprs.e1 = e1;
    ret->subexprs.e2 = e2;

    return ret;
}

struct Expr *mk_div(struct Expr *e1, struct Expr *e2) {
    struct Expr *ret = malloc(sizeof(struct Expr));
    ret->type = DIV;
    ret->subexprs.e1 = e1;
    ret->subexprs.e2 = e2;

    return ret;
}

struct Expr *mk_float(float f) {
    struct Expr *ret = malloc(sizeof(struct Expr));
    ret->type = FLOAT;
    ret->literal = f;

    return ret;
}

/* This function should create the expr (1 + (4 * 5))
 * using the above constructors.
 */
struct Expr *mk_expr1() {
    struct Expr *num1 = mk_float(4);
    struct Expr *num2 = mk_float(5);
    struct Expr *num1_into_num2 = mk_times(num1,num2);
    return mk_plus(mk_float(1),num1_into_num2); 
}

/* This function should create the expr (1 + (7 / 8))
 * using the above constructors.
 */
struct Expr *mk_expr2() {
    struct Expr *num1 = mk_float(7);
    struct Expr *num2 = mk_float(8);
    struct Expr *num1_by_num2 = mk_div(num1,num2);
    return mk_plus(mk_float(1),num1_by_num2);

}

/* This function should create the expr ((1 / 3) - (4 / (2 + 3)))
 * using the above constructors.
 */
struct Expr *mk_expr3() {
    struct Expr *num1 = mk_float(1);
    struct Expr *num2 = mk_float(2);
    struct Expr *num3 = mk_float(3);
    struct Expr *num4 = mk_float(4);

    struct Expr *num2_plus_num3 = mk_plus(num2,num3);
    struct Expr *num4_by_additon_2_3 = mk_div(num4,num2_plus_num3);
    
    struct Expr *num1_by_num3 = mk_div(num1,num3);

    return mk_minus(num1_by_num3,num4_by_additon_2_3);
}


/*
 * This function should free all memory associated 
 * with the given AST.
*/
void free_expr(struct Expr* e) {
    if (e == NULL) return;
    
    if (e->type != FLOAT){
        free_expr(e->subexprs.e1);
        free_expr(e->subexprs.e2);
    }
}

/*
 * This function should evaluate the given AST and
 * return the floating-point result.
*/
float eval(struct Expr* e) {
    switch (e->type){
        case FLOAT:
            return e->literal;
        case PLUS:
            return eval(e->subexprs.e1) + eval(e->subexprs.e2);
        case MINUS:
            return eval(e->subexprs.e1) - eval(e->subexprs.e2);
        case TIMES:
            return eval(e->subexprs.e1) * eval(e->subexprs.e2);
        case DIV:
            return eval(e->subexprs.e1) / eval(e->subexprs.e2);
        default:
            return 0.0;
    }
}




