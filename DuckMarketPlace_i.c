/* WARNING if type checker is not performed, translation could contain errors ! */

#include "DuckMarketPlace.h"

/* Clause CONCRETE_CONSTANTS */
/* Basic constants */

#define DuckMarketPlace__userDummy 0
/* Array and record constants */
/* Clause CONCRETE_VARIABLES */

static int32_t DuckMarketPlace__usuarios_i[10];
static int32_t DuckMarketPlace__creditousuario_i[10];
static int32_t DuckMarketPlace__totalPriceCart_i[10];
static bool DuckMarketPlace__userIdsUsed_i[10];
/* Clause INITIALISATION */
void DuckMarketPlace__INITIALISATION(void)
{
    
    unsigned int i = 0;
    for(i = 0; i <= 9;i++)
    {
        DuckMarketPlace__usuarios_i[i] = DuckMarketPlace__userDummy;
    }
    for(i = 0; i <= 9;i++)
    {
        DuckMarketPlace__creditousuario_i[i] = 0;
    }
    for(i = 0; i <= 9;i++)
    {
        DuckMarketPlace__totalPriceCart_i[i] = 0;
    }
    for(i = 0; i <= 9;i++)
    {
        DuckMarketPlace__userIdsUsed_i[i] = false;
    }
}

/* Clause OPERATIONS */

void DuckMarketPlace__addUser(DuckMarketPlace__IDUSUARIO uu, DuckMarketPlace__NOMEUSUARIO nn, int32_t cc)
{
    DuckMarketPlace__usuarios_i[uu] = nn;
    DuckMarketPlace__creditousuario_i[uu] = cc;
    DuckMarketPlace__totalPriceCart_i[uu] = 0;
    DuckMarketPlace__userIdsUsed_i[uu] = true;
}

void DuckMarketPlace__removeUser(DuckMarketPlace__IDUSUARIO uu)
{
    ;
}

void DuckMarketPlace__altNameUser(DuckMarketPlace__IDUSUARIO uu, DuckMarketPlace__NOMEUSUARIO nn)
{
    ;
}

void DuckMarketPlace__addCredit(DuckMarketPlace__IDUSUARIO uu, int32_t cc)
{
    ;
}

void DuckMarketPlace__withdrawCredit(DuckMarketPlace__IDUSUARIO uu, int32_t cc)
{
    ;
}

void DuckMarketPlace__addProduct(DuckMarketPlace__IDPRODUTO ii, DuckMarketPlace__NOMEPRODUTO nn, DuckMarketPlace__IDUSUARIO uu)
{
    ;
}

void DuckMarketPlace__removeProduct(DuckMarketPlace__IDPRODUTO ii)
{
    ;
}

void DuckMarketPlace__altProductName(DuckMarketPlace__IDPRODUTO ii, DuckMarketPlace__NOMEPRODUTO nn)
{
    ;
}

void DuckMarketPlace__altProductStock(DuckMarketPlace__IDPRODUTO ii, int32_t qq)
{
    ;
}

void DuckMarketPlace__altProductPrice(DuckMarketPlace__IDPRODUTO ii, int32_t pp)
{
    ;
}

void DuckMarketPlace__buyProduct(DuckMarketPlace__IDUSUARIO uu, DuckMarketPlace__IDPRODUTO pp, int32_t qq)
{
    ;
}

void DuckMarketPlace__returnProduct(DuckMarketPlace__IDUSUARIO uu, DuckMarketPlace__IDPRODUTO pp, int32_t rr, int32_t qq)
{
    ;
}

void DuckMarketPlace__addProductToCart(DuckMarketPlace__IDUSUARIO uu, DuckMarketPlace__IDPRODUTO pp, int32_t qq)
{
    ;
}

void DuckMarketPlace__removeProductFromCart(DuckMarketPlace__IDUSUARIO uu, DuckMarketPlace__IDPRODUTO pp, int32_t rr, int32_t qq)
{
    ;
}

void DuckMarketPlace__buyProductsFromCart(DuckMarketPlace__IDUSUARIO uu)
{
    ;
}

void DuckMarketPlace__payDebt(DuckMarketPlace__IDUSUARIO ii)
{
    ;
}

void DuckMarketPlace__payDebtWithCredit(DuckMarketPlace__IDUSUARIO ii, int32_t cc)
{
    ;
}

void DuckMarketPlace__withdrawInactiveCredit(DuckMarketPlace__IDUSUARIO uu)
{
    ;
}

void DuckMarketPlace__removeInactiveUser(DuckMarketPlace__IDUSUARIO uu)
{
    ;
}

void DuckMarketPlace__showUserCredit(DuckMarketPlace__IDUSUARIO uu, int32_t *oo)
{
    ;
}

void DuckMarketPlace__showUserName(DuckMarketPlace__IDUSUARIO uu, DuckMarketPlace__NOMEUSUARIO *oo)
{
    ;
}

void DuckMarketPlace__showUserCartValue(DuckMarketPlace__IDUSUARIO uu, int32_t *oo)
{
    ;
}

void DuckMarketPlace__showUserDebt(DuckMarketPlace__IDUSUARIO uu, int32_t *oo)
{
    ;
}

void DuckMarketPlace__showProductName(DuckMarketPlace__IDPRODUTO pp, DuckMarketPlace__NOMEPRODUTO *oo)
{
    ;
}

void DuckMarketPlace__showProductStock(DuckMarketPlace__IDPRODUTO pp, int32_t *oo)
{
    ;
}

void DuckMarketPlace__showProductPrice(DuckMarketPlace__IDPRODUTO pp, int32_t *oo)
{
    ;
}

void DuckMarketPlace__preAddUser(DuckMarketPlace__IDUSUARIO uu, DuckMarketPlace__NOMEUSUARIO nn, int32_t cc, bool *oo)
{
    bool isUsed;
    
    isUsed = DuckMarketPlace__userIdsUsed_i[uu];
    if((isUsed == false) &&
    ((uu) != (DuckMarketPlace__userDummy)))
    {
        (*oo) = true;
    }
    else
    {
        (*oo) = false;
    }
}

void DuckMarketPlace__preRemoveUser(DuckMarketPlace__IDUSUARIO uu, bool *oo)
{
    ;
}

void DuckMarketPlace__preAltNameUser(DuckMarketPlace__IDUSUARIO uu, DuckMarketPlace__NOMEUSUARIO nn, bool *oo)
{
    ;
}

void DuckMarketPlace__preAddCredit(DuckMarketPlace__IDUSUARIO uu, int32_t cc, bool *oo)
{
    ;
}

void DuckMarketPlace__preWithdrawCredit(DuckMarketPlace__IDUSUARIO uu, int32_t cc, bool *oo)
{
    ;
}

void DuckMarketPlace__preAddProduct(DuckMarketPlace__IDPRODUTO ii, DuckMarketPlace__NOMEPRODUTO nn, DuckMarketPlace__IDUSUARIO uu, bool *oo)
{
    ;
}

void DuckMarketPlace__preRemoveProduct(DuckMarketPlace__IDPRODUTO ii, bool *oo)
{
    ;
}

void DuckMarketPlace__preAltProductName(DuckMarketPlace__IDPRODUTO ii, DuckMarketPlace__NOMEPRODUTO nn, bool *oo)
{
    ;
}

void DuckMarketPlace__preAltProductStock(DuckMarketPlace__IDPRODUTO ii, int32_t qq, bool *oo)
{
    ;
}

void DuckMarketPlace__preAltProductPrice(DuckMarketPlace__IDPRODUTO ii, int32_t pp, bool *oo)
{
    ;
}

void DuckMarketPlace__preBuyProduct(DuckMarketPlace__IDUSUARIO uu, DuckMarketPlace__IDPRODUTO pp, int32_t qq, bool *oo)
{
    ;
}

void DuckMarketPlace__preReturnProduct(DuckMarketPlace__IDUSUARIO uu, DuckMarketPlace__IDPRODUTO pp, int32_t rr, int32_t qq, bool *oo)
{
    ;
}

void DuckMarketPlace__preAddProductToCart(DuckMarketPlace__IDUSUARIO uu, DuckMarketPlace__IDPRODUTO pp, int32_t qq, bool *oo)
{
    ;
}

void DuckMarketPlace__preRemoveProductFromCart(DuckMarketPlace__IDUSUARIO uu, DuckMarketPlace__IDPRODUTO pp, int32_t rr, int32_t qq, bool *oo)
{
    ;
}

void DuckMarketPlace__preBuyProductsFromCart(DuckMarketPlace__IDUSUARIO uu, bool *oo)
{
    ;
}

void DuckMarketPlace__prePayDebt(DuckMarketPlace__IDUSUARIO ii, bool *oo)
{
    ;
}

void DuckMarketPlace__prePayDebtWithCredit(DuckMarketPlace__IDUSUARIO ii, int32_t cc, bool *oo)
{
    ;
}

void DuckMarketPlace__preWithdrawInactiveCredit(DuckMarketPlace__IDUSUARIO uu, bool *oo)
{
    ;
}

void DuckMarketPlace__preRemoveInactiveUser(DuckMarketPlace__IDUSUARIO uu, bool *oo)
{
    ;
}

