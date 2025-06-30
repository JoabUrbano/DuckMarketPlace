#ifndef _DuckMarketPlace_h
#define _DuckMarketPlace_h

#include <stdint.h>
#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#define DuckMarketPlace__NOMEPRODUTO__max 9
#define DuckMarketPlace__NOMEUSUARIO__max 9
#define DuckMarketPlace__IDUSUARIO__max 9
#define DuckMarketPlace__IDPRODUTO__max 9
/* Clause SETS */
typedef int DuckMarketPlace__NOMEPRODUTO;
typedef int DuckMarketPlace__NOMEUSUARIO;
typedef int DuckMarketPlace__IDUSUARIO;
typedef int DuckMarketPlace__IDPRODUTO;

/* Clause CONCRETE_CONSTANTS */
/* Basic constants */
#define DuckMarketPlace__userDummy 0
/* Array and record constants */


/* Clause CONCRETE_VARIABLES */

extern void DuckMarketPlace__INITIALISATION(void);

/* Clause OPERATIONS */

extern void DuckMarketPlace__addUser(DuckMarketPlace__IDUSUARIO uu, DuckMarketPlace__NOMEUSUARIO nn, int32_t cc);
extern void DuckMarketPlace__removeUser(DuckMarketPlace__IDUSUARIO uu);
extern void DuckMarketPlace__altNameUser(DuckMarketPlace__IDUSUARIO uu, DuckMarketPlace__NOMEUSUARIO nn);
extern void DuckMarketPlace__addCredit(DuckMarketPlace__IDUSUARIO uu, int32_t cc);
extern void DuckMarketPlace__withdrawCredit(DuckMarketPlace__IDUSUARIO uu, int32_t cc);
extern void DuckMarketPlace__addProduct(DuckMarketPlace__IDPRODUTO ii, DuckMarketPlace__NOMEPRODUTO nn, DuckMarketPlace__IDUSUARIO uu);
extern void DuckMarketPlace__removeProduct(DuckMarketPlace__IDPRODUTO ii);
extern void DuckMarketPlace__altProductName(DuckMarketPlace__IDPRODUTO ii, DuckMarketPlace__NOMEPRODUTO nn);
extern void DuckMarketPlace__altProductStock(DuckMarketPlace__IDPRODUTO ii, int32_t qq);
extern void DuckMarketPlace__altProductPrice(DuckMarketPlace__IDPRODUTO ii, int32_t pp);
extern void DuckMarketPlace__buyProduct(DuckMarketPlace__IDUSUARIO uu, DuckMarketPlace__IDPRODUTO pp, int32_t qq);
extern void DuckMarketPlace__returnProduct(DuckMarketPlace__IDUSUARIO uu, DuckMarketPlace__IDPRODUTO pp, int32_t rr, int32_t qq);
extern void DuckMarketPlace__addProductToCart(DuckMarketPlace__IDUSUARIO uu, DuckMarketPlace__IDPRODUTO pp, int32_t qq);
extern void DuckMarketPlace__removeProductFromCart(DuckMarketPlace__IDUSUARIO uu, DuckMarketPlace__IDPRODUTO pp, int32_t rr, int32_t qq);
extern void DuckMarketPlace__buyProductsFromCart(DuckMarketPlace__IDUSUARIO uu);
extern void DuckMarketPlace__payDebt(DuckMarketPlace__IDUSUARIO ii);
extern void DuckMarketPlace__payDebtWithCredit(DuckMarketPlace__IDUSUARIO ii, int32_t cc);
extern void DuckMarketPlace__withdrawInactiveCredit(DuckMarketPlace__IDUSUARIO uu);
extern void DuckMarketPlace__removeInactiveUser(DuckMarketPlace__IDUSUARIO uu);
extern void DuckMarketPlace__showUserCredit(DuckMarketPlace__IDUSUARIO uu, int32_t *oo);
extern void DuckMarketPlace__showUserName(DuckMarketPlace__IDUSUARIO uu, DuckMarketPlace__NOMEUSUARIO *oo);
extern void DuckMarketPlace__showUserCartValue(DuckMarketPlace__IDUSUARIO uu, int32_t *oo);
extern void DuckMarketPlace__showUserDebt(DuckMarketPlace__IDUSUARIO uu, int32_t *oo);
extern void DuckMarketPlace__showProductName(DuckMarketPlace__IDPRODUTO pp, DuckMarketPlace__NOMEPRODUTO *oo);
extern void DuckMarketPlace__showProductStock(DuckMarketPlace__IDPRODUTO pp, int32_t *oo);
extern void DuckMarketPlace__showProductPrice(DuckMarketPlace__IDPRODUTO pp, int32_t *oo);
extern void DuckMarketPlace__preAddUser(DuckMarketPlace__IDUSUARIO uu, DuckMarketPlace__NOMEUSUARIO nn, int32_t cc, bool *oo);
extern void DuckMarketPlace__preRemoveUser(DuckMarketPlace__IDUSUARIO uu, bool *oo);
extern void DuckMarketPlace__preAltNameUser(DuckMarketPlace__IDUSUARIO uu, DuckMarketPlace__NOMEUSUARIO nn, bool *oo);
extern void DuckMarketPlace__preAddCredit(DuckMarketPlace__IDUSUARIO uu, int32_t cc, bool *oo);
extern void DuckMarketPlace__preWithdrawCredit(DuckMarketPlace__IDUSUARIO uu, int32_t cc, bool *oo);
extern void DuckMarketPlace__preAddProduct(DuckMarketPlace__IDPRODUTO ii, DuckMarketPlace__NOMEPRODUTO nn, DuckMarketPlace__IDUSUARIO uu, bool *oo);
extern void DuckMarketPlace__preRemoveProduct(DuckMarketPlace__IDPRODUTO ii, bool *oo);
extern void DuckMarketPlace__preAltProductName(DuckMarketPlace__IDPRODUTO ii, DuckMarketPlace__NOMEPRODUTO nn, bool *oo);
extern void DuckMarketPlace__preAltProductStock(DuckMarketPlace__IDPRODUTO ii, int32_t qq, bool *oo);
extern void DuckMarketPlace__preAltProductPrice(DuckMarketPlace__IDPRODUTO ii, int32_t pp, bool *oo);
extern void DuckMarketPlace__preBuyProduct(DuckMarketPlace__IDUSUARIO uu, DuckMarketPlace__IDPRODUTO pp, int32_t qq, bool *oo);
extern void DuckMarketPlace__preReturnProduct(DuckMarketPlace__IDUSUARIO uu, DuckMarketPlace__IDPRODUTO pp, int32_t rr, int32_t qq, bool *oo);
extern void DuckMarketPlace__preAddProductToCart(DuckMarketPlace__IDUSUARIO uu, DuckMarketPlace__IDPRODUTO pp, int32_t qq, bool *oo);
extern void DuckMarketPlace__preRemoveProductFromCart(DuckMarketPlace__IDUSUARIO uu, DuckMarketPlace__IDPRODUTO pp, int32_t rr, int32_t qq, bool *oo);
extern void DuckMarketPlace__preBuyProductsFromCart(DuckMarketPlace__IDUSUARIO uu, bool *oo);
extern void DuckMarketPlace__prePayDebt(DuckMarketPlace__IDUSUARIO ii, bool *oo);
extern void DuckMarketPlace__prePayDebtWithCredit(DuckMarketPlace__IDUSUARIO ii, int32_t cc, bool *oo);
extern void DuckMarketPlace__preWithdrawInactiveCredit(DuckMarketPlace__IDUSUARIO uu, bool *oo);
extern void DuckMarketPlace__preRemoveInactiveUser(DuckMarketPlace__IDUSUARIO uu, bool *oo);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* _DuckMarketPlace_h */
