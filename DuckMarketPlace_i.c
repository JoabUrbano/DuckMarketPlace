/* WARNING if type checker is not performed, translation could contain errors ! */

#include "DuckMarketPlace.h"

/* Clause CONCRETE_CONSTANTS */
/* Basic constants */

#define DuckMarketPlace__userDummy 0
#define DuckMarketPlace__productDummy 0
#define DuckMarketPlace__userIdDummy 0
#define DuckMarketPlace__productIdDummy 0
#define DuckMarketPlace__MAX_PURCHASE 15
/* Array and record constants */
/* Clause CONCRETE_VARIABLES */

static int32_t DuckMarketPlace__usuarios_i[10];
static bool DuckMarketPlace__active_users[10];
static int32_t DuckMarketPlace__dividausuario_i[10];
static bool DuckMarketPlace__dividausuario_aberta_i[10];
static int32_t DuckMarketPlace__usuariosinativos_i[10];
static bool DuckMarketPlace__usersInactive[10];
static int32_t DuckMarketPlace__creditousuario_i[10];
static int32_t DuckMarketPlace__totalPriceCart_i[10];
static bool DuckMarketPlace__userIdsUsed_i[10];
static int32_t DuckMarketPlace__produtos_i[10];
static int32_t DuckMarketPlace__precoproduto_i[10];
static int32_t DuckMarketPlace__estoque_i[10];
static int32_t DuckMarketPlace__dono_i[10];
static int32_t DuckMarketPlace__quantity[10][10];
static int32_t DuckMarketPlace__amount[10][10];
static int32_t DuckMarketPlace__amountProductInCart[10][10];
static int32_t DuckMarketPlace__quantityProductInCart[10][10];
static int32_t DuckMarketPlace__amountProductInLastPurchase[10][10];
static int32_t DuckMarketPlace__quantityProductInLastPurchase[10][10];
static int32_t DuckMarketPlace__purchaseUsers_i[DuckMarketPlace__MAX_PURCHASE+1];
static int32_t DuckMarketPlace__amountPurchaseHistory[DuckMarketPlace__MAX_PURCHASE+1][10];
static int32_t DuckMarketPlace__quantityPurchaseHistory[DuckMarketPlace__MAX_PURCHASE+1][10];
static int32_t DuckMarketPlace__idPurchase_i;
static int32_t DuckMarketPlace__cartSeller_i[10];
static int32_t DuckMarketPlace__allProducts[10];
static int32_t DuckMarketPlace__countAllProducts;
/* Clause INITIALISATION */
void DuckMarketPlace__INITIALISATION(void)
{
    
    unsigned int i = 0, j= 0;
    for(i = 0; i <= 9;i++)
    {
        DuckMarketPlace__usuarios_i[i] = DuckMarketPlace__userDummy;
    }
    for(i = 0; i <= 9;i++)
    {
        DuckMarketPlace__active_users[i] = false;
    }
    for(i = 0; i <= 9;i++)
    {
        DuckMarketPlace__dividausuario_i[i] = 0;
    }
    for(i = 0; i <= 9;i++)
    {
        DuckMarketPlace__dividausuario_aberta_i[i] = false;
    }
    for(i = 0; i <= 9;i++)
    {
        DuckMarketPlace__usuariosinativos_i[i] = 0;
    }
    for(i = 0; i <= 9;i++)
    {
        DuckMarketPlace__usersInactive[i] = false;
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
    for(i = 0; i <= 9;i++)
    {
        DuckMarketPlace__produtos_i[i] = DuckMarketPlace__productDummy;
    }
    for(i = 0; i <= 9;i++)
    {
        DuckMarketPlace__precoproduto_i[i] = 0;
    }
    for(i = 0; i <= 9;i++)
    {
        DuckMarketPlace__estoque_i[i] = 0;
    }
    for(i = 0; i <= 9;i++)
    {
        DuckMarketPlace__dono_i[i] = DuckMarketPlace__userIdDummy;
    }
    for(i = 0; i <= 9;i++)
    {
        for(j = 0; j <= 9;j++)
        {
            DuckMarketPlace__quantity[i][j] = 0;
        }
    }
    for(i = 0; i <= 9;i++)
    {
        for(j = 0; j <= 9;j++)
        {
            DuckMarketPlace__amount[i][j] = 0;
        }
    }
    for(i = 0; i <= 9;i++)
    {
        for(j = 0; j <= 9;j++)
        {
            DuckMarketPlace__quantityProductInCart[i][j] = 0;
        }
    }
    for(i = 0; i <= 9;i++)
    {
        for(j = 0; j <= 9;j++)
        {
            DuckMarketPlace__amountProductInCart[i][j] = 0;
        }
    }
    for(i = 0; i <= 9;i++)
    {
        for(j = 0; j <= 9;j++)
        {
            DuckMarketPlace__amountProductInLastPurchase[i][j] = 0;
        }
    }
    for(i = 0; i <= 9;i++)
    {
        for(j = 0; j <= 9;j++)
        {
            DuckMarketPlace__quantityProductInLastPurchase[i][j] = 0;
        }
    }
    for(i = 0; i <= DuckMarketPlace__MAX_PURCHASE;i++)
    {
        DuckMarketPlace__purchaseUsers_i[i] = DuckMarketPlace__userIdDummy;
    }
    for(i = 0; i <= DuckMarketPlace__MAX_PURCHASE;i++)
    {
        for(j = 0; j <= 9;j++)
        {
            DuckMarketPlace__amountPurchaseHistory[i][j] = 0;
        }
    }
    for(i = 0; i <= DuckMarketPlace__MAX_PURCHASE;i++)
    {
        for(j = 0; j <= 9;j++)
        {
            DuckMarketPlace__quantityPurchaseHistory[i][j] = 0;
        }
    }
    DuckMarketPlace__idPurchase_i = 0;
    for(i = 0; i <= 9;i++)
    {
        DuckMarketPlace__cartSeller_i[i] = DuckMarketPlace__userIdDummy;
    }
    for(i = 0; i <= 9;i++)
    {
        DuckMarketPlace__allProducts[i] = DuckMarketPlace__productIdDummy;
    }
    DuckMarketPlace__countAllProducts = 0;
}

/* Clause OPERATIONS */

void DuckMarketPlace__addUser(DuckMarketPlace__IDUSUARIO uu, DuckMarketPlace__NOMEUSUARIO nn, int32_t cc)
{
    DuckMarketPlace__usuarios_i[uu] = nn;
    DuckMarketPlace__creditousuario_i[uu] = cc;
    DuckMarketPlace__active_users[uu] = true;
    DuckMarketPlace__totalPriceCart_i[uu] = 0;
    DuckMarketPlace__userIdsUsed_i[uu] = true;
}

void DuckMarketPlace__removeUser(DuckMarketPlace__IDUSUARIO uu)
{
    DuckMarketPlace__usuarios_i[uu] = DuckMarketPlace__userDummy;
    DuckMarketPlace__totalPriceCart_i[uu] = 0;
    DuckMarketPlace__active_users[uu] = false;
    DuckMarketPlace__cartSeller_i[uu] = DuckMarketPlace__userIdDummy;
    {
        int32_t userCredits;
        
        userCredits = DuckMarketPlace__creditousuario_i[uu];
        if((userCredits) >= (0))
        {
            DuckMarketPlace__usuariosinativos_i[uu] = userCredits;
            DuckMarketPlace__usersInactive[uu] = true;
        }
        DuckMarketPlace__creditousuario_i[uu] = 0;
    }
    {
        int32_t index;
        int32_t range;
        int32_t dono_loop;
        int32_t pp;
        
        index = 0;
        range = DuckMarketPlace__countAllProducts;
        while((index) < (range))
        {
            pp = DuckMarketPlace__allProducts[index];
            dono_loop = DuckMarketPlace__dono_i[pp];
            if(dono_loop == uu)
            {
                DuckMarketPlace__produtos_i[pp] = DuckMarketPlace__productDummy;
                DuckMarketPlace__estoque_i[pp] = 0;
                DuckMarketPlace__precoproduto_i[pp] = 0;
            }
            DuckMarketPlace__quantity[uu][pp] = 0;
            DuckMarketPlace__amount[uu][pp] = 0;
            DuckMarketPlace__amountProductInCart[uu][pp] = 0;
            DuckMarketPlace__quantityProductInCart[uu][pp] = 0;
            {
                int32_t count;
                int32_t currentUserId;
                
                count = 0;
                currentUserId = DuckMarketPlace__userIdDummy;
                while((count) <= (DuckMarketPlace__MAX_PURCHASE))
                {
                    currentUserId = DuckMarketPlace__purchaseUsers_i[count];
                    if(uu == currentUserId)
                    {
                        DuckMarketPlace__quantityPurchaseHistory[count][pp] = 0;
                        DuckMarketPlace__amountPurchaseHistory[count][pp] = 0;
                        DuckMarketPlace__purchaseUsers_i[count] = DuckMarketPlace__userIdDummy;
                    }
                    count = count+1;
                }
            }
            index = index+1;
        }
    }
}

void DuckMarketPlace__altNameUser(DuckMarketPlace__IDUSUARIO uu, DuckMarketPlace__NOMEUSUARIO nn)
{
    DuckMarketPlace__usuarios_i[uu] = nn;
}

void DuckMarketPlace__addCredit(DuckMarketPlace__IDUSUARIO uu, int32_t cc)
{
    DuckMarketPlace__creditousuario_i[uu] = DuckMarketPlace__creditousuario_i[uu]+cc;
}

void DuckMarketPlace__withdrawCredit(DuckMarketPlace__IDUSUARIO uu, int32_t cc)
{
    DuckMarketPlace__creditousuario_i[uu] = DuckMarketPlace__creditousuario_i[uu]-cc;
}

void DuckMarketPlace__addProduct(DuckMarketPlace__IDPRODUTO ii, DuckMarketPlace__NOMEPRODUTO nn, DuckMarketPlace__IDUSUARIO uu, int32_t qq, int32_t pp)
{
    DuckMarketPlace__produtos_i[ii] = nn;
    DuckMarketPlace__dono_i[ii] = uu;
    DuckMarketPlace__estoque_i[ii] = qq;
    DuckMarketPlace__precoproduto_i[ii] = pp;
    DuckMarketPlace__allProducts[DuckMarketPlace__countAllProducts] = ii;
    DuckMarketPlace__countAllProducts = DuckMarketPlace__countAllProducts+1;
}

void DuckMarketPlace__removeProduct(DuckMarketPlace__IDPRODUTO ii)
{
    DuckMarketPlace__produtos_i[ii] = DuckMarketPlace__productDummy;
    DuckMarketPlace__estoque_i[ii] = 0;
    DuckMarketPlace__dono_i[ii] = DuckMarketPlace__userIdDummy;
    DuckMarketPlace__precoproduto_i[ii] = 0;
    {
        int32_t index;
        int32_t range;
        int32_t pp;
        
        index = 0;
        range = DuckMarketPlace__countAllProducts;
        while((index) < (range))
        {
            pp = DuckMarketPlace__allProducts[index];
            if(pp == ii)
            {
                DuckMarketPlace__allProducts[index] = DuckMarketPlace__productIdDummy;
            }
            index = index+1;
        }
    }
    DuckMarketPlace__countAllProducts = DuckMarketPlace__countAllProducts-1;
}

void DuckMarketPlace__altProductName(DuckMarketPlace__IDPRODUTO ii, DuckMarketPlace__NOMEPRODUTO nn)
{
    DuckMarketPlace__produtos_i[ii] = nn;
}

void DuckMarketPlace__altProductStock(DuckMarketPlace__IDPRODUTO ii, int32_t qq)
{
    DuckMarketPlace__estoque_i[ii] = qq;
}

void DuckMarketPlace__altProductPrice(DuckMarketPlace__IDPRODUTO ii, int32_t pp)
{
    DuckMarketPlace__precoproduto_i[ii] = pp;
}

void DuckMarketPlace__buyProduct(DuckMarketPlace__IDUSUARIO uu, DuckMarketPlace__IDPRODUTO pp, int32_t qq)
{
    DuckMarketPlace__quantity[uu][pp] = qq;
    DuckMarketPlace__amount[uu][pp] = DuckMarketPlace__precoproduto_i[pp];
    DuckMarketPlace__amountPurchaseHistory[DuckMarketPlace__idPurchase_i][pp] = DuckMarketPlace__precoproduto_i[pp];
    DuckMarketPlace__quantityPurchaseHistory[DuckMarketPlace__idPurchase_i][pp] = qq;
    DuckMarketPlace__idPurchase_i = DuckMarketPlace__idPurchase_i+1;
    {
        int32_t productOwner;
        
        productOwner = DuckMarketPlace__dono_i[pp];
        DuckMarketPlace__creditousuario_i[productOwner] = DuckMarketPlace__creditousuario_i[productOwner]+(DuckMarketPlace__precoproduto_i[pp] * qq);
        DuckMarketPlace__creditousuario_i[uu] = DuckMarketPlace__creditousuario_i[uu]-(DuckMarketPlace__precoproduto_i[pp] * qq);
    }
    DuckMarketPlace__estoque_i[pp] = DuckMarketPlace__estoque_i[pp]-qq;
}

void DuckMarketPlace__returnProduct(DuckMarketPlace__IDUSUARIO uu, DuckMarketPlace__IDPRODUTO pp, int32_t rr, int32_t qq)
{
    {
        int32_t ownerProduct;
        
        ownerProduct = DuckMarketPlace__dono_i[pp];
        DuckMarketPlace__dividausuario_i[ownerProduct] = DuckMarketPlace__dividausuario_i[ownerProduct]+(qq * rr);
    }
    DuckMarketPlace__creditousuario_i[uu] = DuckMarketPlace__creditousuario_i[uu]+(qq * rr);
    DuckMarketPlace__quantity[uu][pp] = DuckMarketPlace__quantity[uu][pp]-qq;
    {
        int32_t count;
        int32_t lastIdPurchaseUser;
        int32_t currentUserId;
        
        count = 0;
        lastIdPurchaseUser = 0;
        currentUserId = DuckMarketPlace__userIdDummy;
        while((count) <= (DuckMarketPlace__MAX_PURCHASE))
        {
            currentUserId = DuckMarketPlace__purchaseUsers_i[count];
            if(uu == currentUserId)
            {
                lastIdPurchaseUser = count;
            }
            count = count+1;
        }
        DuckMarketPlace__quantityPurchaseHistory[lastIdPurchaseUser][pp] = DuckMarketPlace__quantityPurchaseHistory[lastIdPurchaseUser][pp]-qq;
    }
    {
        int32_t productName;
        
        productName = DuckMarketPlace__produtos_i[pp];
        if((productName) != (DuckMarketPlace__productDummy))
        {
            DuckMarketPlace__estoque_i[pp] = DuckMarketPlace__estoque_i[pp]+qq;
        }
    }
}

void DuckMarketPlace__addProductToCart(DuckMarketPlace__IDUSUARIO uu, DuckMarketPlace__IDPRODUTO pp, int32_t qq)
{
    DuckMarketPlace__cartSeller_i[uu] = DuckMarketPlace__dono_i[pp];
    DuckMarketPlace__quantityProductInCart[uu][pp] = DuckMarketPlace__quantityProductInCart[uu][pp]+qq;
    DuckMarketPlace__amountProductInCart[uu][pp] = DuckMarketPlace__precoproduto_i[pp];
    DuckMarketPlace__totalPriceCart_i[uu] = DuckMarketPlace__totalPriceCart_i[uu]+(DuckMarketPlace__precoproduto_i[pp] * qq);
    DuckMarketPlace__estoque_i[pp] = DuckMarketPlace__estoque_i[pp]-qq;
}

void DuckMarketPlace__removeProductFromCart(DuckMarketPlace__IDUSUARIO uu, DuckMarketPlace__IDPRODUTO pp, int32_t rr, int32_t qq)
{
    DuckMarketPlace__quantityProductInCart[uu][pp] = DuckMarketPlace__quantityProductInCart[uu][pp]-qq;
    {
        int32_t quantityProduct;
        
        quantityProduct = DuckMarketPlace__quantityProductInCart[uu][pp];
        if(quantityProduct == 0)
        {
            DuckMarketPlace__amountProductInCart[uu][pp] = 0;
        }
    }
    DuckMarketPlace__totalPriceCart_i[uu] = DuckMarketPlace__totalPriceCart_i[uu]-(DuckMarketPlace__precoproduto_i[pp] * qq);
    {
        int32_t productName;
        
        productName = DuckMarketPlace__produtos_i[pp];
        if((productName) != (DuckMarketPlace__productDummy))
        {
            DuckMarketPlace__estoque_i[pp] = DuckMarketPlace__estoque_i[pp]+qq;
        }
    }
    {
        int32_t index;
        int32_t range;
        int32_t productWhile;
        bool haveNoProducts;
        int32_t quantityWhile;
        
        index = 0;
        range = DuckMarketPlace__countAllProducts;
        haveNoProducts = true;
        while((index) < (range))
        {
            productWhile = DuckMarketPlace__allProducts[index];
            quantityWhile = DuckMarketPlace__quantityProductInCart[uu][productWhile];
            if((quantityWhile) > (0))
            {
                haveNoProducts = false;
            }
            index = index+1;
        }
        if(haveNoProducts == true)
        {
            DuckMarketPlace__cartSeller_i[uu] = DuckMarketPlace__userIdDummy;
        }
    }
}

void DuckMarketPlace__buyProductsFromCart(DuckMarketPlace__IDUSUARIO uu)
{
    DuckMarketPlace__creditousuario_i[uu] = DuckMarketPlace__creditousuario_i[uu]-DuckMarketPlace__totalPriceCart_i[uu];
    DuckMarketPlace__creditousuario_i[DuckMarketPlace__cartSeller_i[uu]] = DuckMarketPlace__creditousuario_i[DuckMarketPlace__cartSeller_i[uu]]+DuckMarketPlace__totalPriceCart_i[uu];
    DuckMarketPlace__totalPriceCart_i[uu] = 0;
    {
        int32_t index;
        int32_t range;
        int32_t productWhile;
        
        index = 0;
        range = DuckMarketPlace__countAllProducts;
        while((index) < (range))
        {
            productWhile = DuckMarketPlace__allProducts[index];
            DuckMarketPlace__quantityProductInLastPurchase[uu][productWhile] = DuckMarketPlace__quantityProductInCart[uu][productWhile];
            DuckMarketPlace__amountProductInLastPurchase[uu][productWhile] = DuckMarketPlace__amountProductInCart[uu][productWhile];
            DuckMarketPlace__quantityPurchaseHistory[DuckMarketPlace__idPurchase_i][productWhile] = DuckMarketPlace__quantityProductInCart[uu][productWhile];
            DuckMarketPlace__amountPurchaseHistory[DuckMarketPlace__idPurchase_i][productWhile] = DuckMarketPlace__amountProductInCart[uu][productWhile];
            DuckMarketPlace__quantityProductInCart[uu][productWhile] = 0;
            DuckMarketPlace__amountProductInCart[uu][productWhile] = 0;
            index = index+1;
        }
    }
    DuckMarketPlace__cartSeller_i[uu] = DuckMarketPlace__userIdDummy;
    DuckMarketPlace__purchaseUsers_i[DuckMarketPlace__idPurchase_i] = uu;
    DuckMarketPlace__idPurchase_i = DuckMarketPlace__idPurchase_i+1;
}

void DuckMarketPlace__payDebt(DuckMarketPlace__IDUSUARIO uu)
{
    {
        int32_t divida;
        int32_t credito;
        
        divida = DuckMarketPlace__dividausuario_i[uu];
        credito = DuckMarketPlace__creditousuario_i[uu];
        if((divida) <= (credito))
        {
            DuckMarketPlace__creditousuario_i[uu] = credito-divida;
            DuckMarketPlace__dividausuario_i[uu] = 0;
            DuckMarketPlace__dividausuario_aberta_i[uu] = false;
        }
        else
        {
            DuckMarketPlace__dividausuario_i[uu] = divida-credito;
            DuckMarketPlace__creditousuario_i[uu] = 0;
        }
    }
}

void DuckMarketPlace__payDebtWithCredit(DuckMarketPlace__IDUSUARIO uu, int32_t cc)
{
    {
        int32_t divida;
        
        divida = DuckMarketPlace__dividausuario_i[uu];
        if((divida) <= (cc))
        {
            DuckMarketPlace__dividausuario_i[uu] = 0;
            DuckMarketPlace__dividausuario_aberta_i[uu] = false;
        }
        else
        {
            DuckMarketPlace__dividausuario_i[uu] = divida-cc;
        }
    }
}

void DuckMarketPlace__withdrawInactiveCredit(DuckMarketPlace__IDUSUARIO uu)
{
    DuckMarketPlace__usuariosinativos_i[uu] = 0;
}

void DuckMarketPlace__removeInactiveUser(DuckMarketPlace__IDUSUARIO uu)
{
    DuckMarketPlace__usersInactive[uu] = false;
}

void DuckMarketPlace__showUserCredit(DuckMarketPlace__IDUSUARIO uu, int32_t *oo)
{
    {
        int32_t isNotDummy;
        
        isNotDummy = DuckMarketPlace__usuarios_i[uu];
        if((isNotDummy) != (DuckMarketPlace__userDummy))
        {
            (*oo) = DuckMarketPlace__creditousuario_i[uu];
        }
    }
}

void DuckMarketPlace__showUserName(DuckMarketPlace__IDUSUARIO uu, DuckMarketPlace__NOMEUSUARIO *oo)
{
    {
        int32_t isDummy;
        
        isDummy = DuckMarketPlace__usuarios_i[uu];
        if((isDummy) != (DuckMarketPlace__userDummy))
        {
            (*oo) = DuckMarketPlace__usuarios_i[uu];
        }
    }
}

void DuckMarketPlace__showUserCartValue(DuckMarketPlace__IDUSUARIO uu, int32_t *oo)
{
    int32_t isDummy;
    
    isDummy = DuckMarketPlace__usuarios_i[uu];
    if((isDummy) != (DuckMarketPlace__userDummy))
    {
        (*oo) = DuckMarketPlace__totalPriceCart_i[uu];
    }
}

void DuckMarketPlace__showUserDebt(DuckMarketPlace__IDUSUARIO uu, int32_t *oo)
{
    int32_t isDummy;
    
    isDummy = DuckMarketPlace__usuarios_i[uu];
    if((isDummy) != (DuckMarketPlace__userDummy))
    {
        (*oo) = DuckMarketPlace__dividausuario_i[uu];
    }
}

void DuckMarketPlace__showProductName(DuckMarketPlace__IDPRODUTO pp, DuckMarketPlace__NOMEPRODUTO *oo)
{
    {
        int32_t isProductDummy;
        
        isProductDummy = DuckMarketPlace__produtos_i[pp];
        if((isProductDummy) != (DuckMarketPlace__productDummy))
        {
            (*oo) = DuckMarketPlace__produtos_i[pp];
        }
    }
}

void DuckMarketPlace__showProductStock(DuckMarketPlace__IDPRODUTO pp, int32_t *oo)
{
    {
        int32_t isProductDummy;
        
        isProductDummy = DuckMarketPlace__produtos_i[pp];
        if((isProductDummy) != (DuckMarketPlace__productDummy))
        {
            (*oo) = DuckMarketPlace__estoque_i[pp];
        }
    }
}

void DuckMarketPlace__showProductPrice(DuckMarketPlace__IDPRODUTO pp, int32_t *oo)
{
    {
        int32_t isProductDummy;
        
        isProductDummy = DuckMarketPlace__produtos_i[pp];
        if((isProductDummy) != (DuckMarketPlace__productDummy))
        {
            (*oo) = DuckMarketPlace__precoproduto_i[pp];
        }
    }
}

void DuckMarketPlace__preAddUser(DuckMarketPlace__IDUSUARIO uu, DuckMarketPlace__NOMEUSUARIO nn, int32_t cc, bool *oo)
{
    bool isIdUsed;
    bool isActived;
    int32_t name;
    
    isIdUsed = DuckMarketPlace__userIdsUsed_i[uu];
    isActived = DuckMarketPlace__active_users[uu];
    name = DuckMarketPlace__usuarios_i[uu];
    if((((((isIdUsed == false) &&
                    (isActived == false)) &&
                ((nn) != (DuckMarketPlace__userDummy))) &&
            (name == DuckMarketPlace__userDummy)) &&
        ((uu) != (DuckMarketPlace__userIdDummy))) &&
    ((cc) <= (2147483647)))
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
    bool isUsed;
    bool isActived;
    int32_t name;
    bool hasDebt;
    
    isUsed = DuckMarketPlace__userIdsUsed_i[uu];
    isActived = DuckMarketPlace__active_users[uu];
    name = DuckMarketPlace__usuarios_i[uu];
    hasDebt = DuckMarketPlace__dividausuario_aberta_i[uu];
    if(((((isUsed == true) &&
                (isActived == true)) &&
            ((name) != (DuckMarketPlace__userDummy))) &&
        (hasDebt == false)) &&
    ((uu) != (DuckMarketPlace__userIdDummy)))
    {
        (*oo) = true;
    }
    else
    {
        (*oo) = false;
    }
}

void DuckMarketPlace__preAltNameUser(DuckMarketPlace__IDUSUARIO uu, DuckMarketPlace__NOMEUSUARIO nn, bool *oo)
{
    int32_t exist;
    
    exist = DuckMarketPlace__usuarios_i[uu];
    if((((exist) != (DuckMarketPlace__userDummy)) &&
        ((nn) != (DuckMarketPlace__userDummy))) &&
    ((uu) != (DuckMarketPlace__userIdDummy)))
    {
        (*oo) = true;
    }
    else
    {
        (*oo) = false;
    }
}

void DuckMarketPlace__preAddCredit(DuckMarketPlace__IDUSUARIO uu, int32_t cc, bool *oo)
{
    {
        bool isActived;
        int32_t userCreditSum;
        
        isActived = DuckMarketPlace__active_users[uu];
        userCreditSum = DuckMarketPlace__creditousuario_i[uu]+cc;
        if(((((isActived == true) &&
                    ((userCreditSum) <= (2147483647))) &&
                ((cc) > (0))) &&
            ((cc) <= (2147483647))) &&
        ((uu) != (DuckMarketPlace__userIdDummy)))
        {
            (*oo) = true;
        }
        else
        {
            (*oo) = false;
        }
    }
}

void DuckMarketPlace__preWithdrawCredit(DuckMarketPlace__IDUSUARIO uu, int32_t cc, bool *oo)
{
    {
        bool isActived;
        int32_t userCreditSub;
        bool userHasDebt;
        int32_t userCredits;
        
        isActived = DuckMarketPlace__active_users[uu];
        userCreditSub = DuckMarketPlace__creditousuario_i[uu]-cc;
        userHasDebt = DuckMarketPlace__dividausuario_aberta_i[uu];
        userCredits = DuckMarketPlace__creditousuario_i[uu];
        if(((((((isActived == true) &&
                            ((cc) > (0))) &&
                        ((cc) <= (2147483647))) &&
                    ((userCreditSub) >= (0))) &&
                (userHasDebt == false)) &&
            ((cc) <= (userCredits))) &&
        ((uu) != (DuckMarketPlace__userIdDummy)))
        {
            (*oo) = true;
        }
        else
        {
            (*oo) = false;
        }
    }
}

void DuckMarketPlace__preAddProduct(DuckMarketPlace__IDPRODUTO ii, DuckMarketPlace__NOMEPRODUTO nn, DuckMarketPlace__IDUSUARIO uu, int32_t qq, int32_t pp, bool *oo)
{
    {
        int32_t prudctIsDummy;
        int32_t donoIsDummy;
        bool isActived;
        
        isActived = DuckMarketPlace__active_users[uu];
        prudctIsDummy = DuckMarketPlace__produtos_i[ii];
        donoIsDummy = DuckMarketPlace__dono_i[ii];
        if(((((((((qq) <= (2147483647)) &&
                                ((pp) <= (2147483647))) &&
                            (isActived == true)) &&
                        (prudctIsDummy == DuckMarketPlace__productDummy)) &&
                    (donoIsDummy == DuckMarketPlace__userIdDummy)) &&
                ((uu) != (DuckMarketPlace__userIdDummy))) &&
            ((nn) != (DuckMarketPlace__productDummy))) &&
        ((ii) != (DuckMarketPlace__productIdDummy)))
        {
            (*oo) = true;
        }
        else
        {
            (*oo) = false;
        }
    }
}

void DuckMarketPlace__preRemoveProduct(DuckMarketPlace__IDPRODUTO ii, bool *oo)
{
    {
        int32_t prudctIsDummy;
        int32_t donoIsDummy;
        
        prudctIsDummy = DuckMarketPlace__produtos_i[ii];
        donoIsDummy = DuckMarketPlace__dono_i[ii];
        if(((prudctIsDummy) != (DuckMarketPlace__productDummy)) &&
        ((donoIsDummy) != (DuckMarketPlace__userIdDummy)))
        {
            (*oo) = true;
        }
        else
        {
            (*oo) = false;
        }
    }
}

void DuckMarketPlace__preAltProductName(DuckMarketPlace__IDPRODUTO ii, DuckMarketPlace__NOMEPRODUTO nn, bool *oo)
{
    int32_t np;
    
    np = DuckMarketPlace__produtos_i[ii];
    if((((np) != (DuckMarketPlace__productDummy)) &&
        ((nn) != (DuckMarketPlace__productDummy))) &&
    ((ii) != (DuckMarketPlace__productIdDummy)))
    {
        (*oo) = true;
    }
    else
    {
        (*oo) = false;
    }
}

void DuckMarketPlace__preAltProductStock(DuckMarketPlace__IDPRODUTO ii, int32_t qq, bool *oo)
{
    int32_t np;
    
    np = DuckMarketPlace__produtos_i[ii];
    if(((((np) != (DuckMarketPlace__productDummy)) &&
            ((qq) <= (2147483647))) &&
        ((ii) != (DuckMarketPlace__productIdDummy))) &&
    ((qq) > (0)))
    {
        (*oo) = true;
    }
    else
    {
        (*oo) = false;
    }
}

void DuckMarketPlace__preAltProductPrice(DuckMarketPlace__IDPRODUTO ii, int32_t pp, bool *oo)
{
    int32_t np;
    
    np = DuckMarketPlace__produtos_i[ii];
    if(((((np) != (DuckMarketPlace__productDummy)) &&
            ((pp) <= (2147483647))) &&
        ((ii) != (DuckMarketPlace__productIdDummy))) &&
    ((pp) > (0)))
    {
        (*oo) = true;
    }
    else
    {
        (*oo) = false;
    }
}

void DuckMarketPlace__preBuyProduct(DuckMarketPlace__IDUSUARIO uu, DuckMarketPlace__IDPRODUTO pp, int32_t qq, bool *oo)
{
    int32_t buyer;
    int32_t item;
    int32_t seller;
    int32_t stockProduct;
    int32_t productPrice;
    int32_t buyerCredits;
    int32_t sellerCredits;
    int32_t purchasePrice;
    int32_t newSellerCredits;
    
    buyer = DuckMarketPlace__usuarios_i[uu];
    item = DuckMarketPlace__produtos_i[pp];
    seller = DuckMarketPlace__dono_i[pp];
    stockProduct = DuckMarketPlace__estoque_i[pp];
    productPrice = DuckMarketPlace__precoproduto_i[pp];
    buyerCredits = DuckMarketPlace__creditousuario_i[uu];
    sellerCredits = DuckMarketPlace__creditousuario_i[seller];
    purchasePrice = productPrice * qq;
    newSellerCredits = sellerCredits+(productPrice * qq);
    if((((((((((((buyer) != (DuckMarketPlace__userDummy)) &&
                                        ((item) != (DuckMarketPlace__productDummy))) &&
                                    ((uu) != (seller))) &&
                                ((qq) > (0))) &&
                            ((qq) <= (2147483647))) &&
                        ((qq) <= (stockProduct))) &&
                    ((purchasePrice) <= (buyerCredits))) &&
                ((newSellerCredits) <= (2147483647))) &&
            ((DuckMarketPlace__idPurchase_i) < (DuckMarketPlace__MAX_PURCHASE))) &&
        ((pp) != (DuckMarketPlace__productIdDummy))) &&
    ((uu) != (DuckMarketPlace__userIdDummy)))
    {
        (*oo) = true;
    }
    else
    {
        (*oo) = false;
    }
}

void DuckMarketPlace__preReturnProduct(DuckMarketPlace__IDUSUARIO uu, DuckMarketPlace__IDPRODUTO pp, int32_t rr, int32_t qq, bool *oo)
{
    int32_t nu;
    int32_t np;
    int32_t ee;
    int32_t pd;
    int32_t cu;
    int32_t qqEe;
    int32_t am;
    int32_t du;
    int32_t amDu;
    int32_t qlp;
    int32_t alp;
    
    nu = DuckMarketPlace__usuarios_i[uu];
    np = DuckMarketPlace__produtos_i[pp];
    ee = DuckMarketPlace__estoque_i[pp];
    pd = DuckMarketPlace__precoproduto_i[pp];
    cu = DuckMarketPlace__creditousuario_i[uu];
    qqEe = qq+ee;
    qlp = DuckMarketPlace__quantityProductInLastPurchase[uu][pp];
    alp = DuckMarketPlace__amountProductInLastPurchase[uu][pp];
    am = qlp * rr;
    du = DuckMarketPlace__dividausuario_i[DuckMarketPlace__dono_i[pp]];
    amDu = du+am;
    if((((((((((nu) != (DuckMarketPlace__userDummy)) &&
                                ((np) != (DuckMarketPlace__productDummy))) &&
                            ((rr) <= (2147483647))) &&
                        ((qq) > (0))) &&
                    ((qq) <= (2147483647))) &&
                ((qqEe) <= (2147483647))) &&
            ((amDu) <= (2147483647))) &&
        ((qq) <= (qlp))) &&
    (alp == rr))
    {
        (*oo) = true;
    }
    else
    {
        (*oo) = false;
    }
}

void DuckMarketPlace__preAddProductToCart(DuckMarketPlace__IDUSUARIO uu, DuckMarketPlace__IDPRODUTO pp, int32_t qq, bool *oo)
{
    int32_t nu;
    int32_t np;
    int32_t dd;
    int32_t ee;
    int32_t qpc;
    int32_t qccQq;
    int32_t cs;
    int32_t tp;
    int32_t ppd;
    int32_t newTotal;
    
    nu = DuckMarketPlace__usuarios_i[uu];
    np = DuckMarketPlace__produtos_i[pp];
    dd = DuckMarketPlace__dono_i[pp];
    ee = DuckMarketPlace__estoque_i[pp];
    qpc = DuckMarketPlace__quantityProductInCart[uu][pp];
    qccQq = qq+qpc;
    cs = DuckMarketPlace__cartSeller_i[uu];
    tp = DuckMarketPlace__totalPriceCart_i[uu];
    ppd = DuckMarketPlace__precoproduto_i[pp];
    newTotal = tp+(qq * ppd);
    if((((((((((nu) != (DuckMarketPlace__userDummy)) &&
                                ((np) != (DuckMarketPlace__productDummy))) &&
                            ((qq) > (0))) &&
                        ((qq) <= (2147483647))) &&
                    ((uu) != (dd))) &&
                ((qq) <= (ee))) &&
            ((qccQq) <= (2147483647))) &&
        (((cs == DuckMarketPlace__userIdDummy) ||
                (cs == dd)))) &&
    ((newTotal) <= (2147483647)))
    {
        (*oo) = true;
    }
    else
    {
        (*oo) = false;
    }
}

void DuckMarketPlace__preRemoveProductFromCart(DuckMarketPlace__IDUSUARIO uu, DuckMarketPlace__IDPRODUTO pp, int32_t rr, int32_t qq, bool *oo)
{
    int32_t nu;
    int32_t np;
    int32_t ee;
    int32_t qpc;
    int32_t qqEe;
    int32_t apc;
    
    nu = DuckMarketPlace__usuarios_i[uu];
    np = DuckMarketPlace__produtos_i[pp];
    ee = DuckMarketPlace__estoque_i[pp];
    qpc = DuckMarketPlace__quantityProductInCart[uu][pp];
    qqEe = qq+ee;
    apc = DuckMarketPlace__amountProductInCart[uu][pp];
    if(((((((((nu) != (DuckMarketPlace__userDummy)) &&
                            ((np) != (DuckMarketPlace__productDummy))) &&
                        ((qq) > (0))) &&
                    ((qq) <= (2147483647))) &&
                ((rr) <= (2147483647))) &&
            ((qq) <= (qpc))) &&
        ((qqEe) <= (2147483647))) &&
    (rr == apc))
    {
        (*oo) = true;
    }
    else
    {
        (*oo) = false;
    }
}

void DuckMarketPlace__preBuyProductsFromCart(DuckMarketPlace__IDUSUARIO uu, bool *oo)
{
    int32_t cu;
    int32_t tp;
    int32_t cs;
    int32_t nd;
    int32_t cuCs;
    int32_t cuCsTp;
    
    cu = DuckMarketPlace__creditousuario_i[uu];
    tp = DuckMarketPlace__totalPriceCart_i[uu];
    cs = DuckMarketPlace__cartSeller_i[uu];
    nd = DuckMarketPlace__usuarios_i[cs];
    cuCs = DuckMarketPlace__creditousuario_i[cs];
    cuCsTp = cuCs+tp;
    if(((((cu) >= (tp)) &&
            ((DuckMarketPlace__idPurchase_i) < (DuckMarketPlace__MAX_PURCHASE))) &&
        ((nd) != (DuckMarketPlace__userDummy))) &&
    ((cuCsTp) <= (2147483647)))
    {
        (*oo) = true;
    }
    else
    {
        (*oo) = false;
    }
}

void DuckMarketPlace__prePayDebt(DuckMarketPlace__IDUSUARIO uu, bool *oo)
{
    bool inDebt;
    int32_t isActive;
    
    inDebt = DuckMarketPlace__dividausuario_aberta_i[uu];
    isActive = DuckMarketPlace__usuarios_i[uu];
    if((inDebt == true) &&
    ((isActive) != (DuckMarketPlace__userDummy)))
    {
        (*oo) = true;
    }
    else
    {
        (*oo) = false;
    }
}

void DuckMarketPlace__prePayDebtWithCredit(DuckMarketPlace__IDUSUARIO uu, int32_t cc, bool *oo)
{
    bool inDebt;
    
    inDebt = DuckMarketPlace__dividausuario_aberta_i[uu];
    if(inDebt == true)
    {
        (*oo) = true;
    }
    else
    {
        (*oo) = false;
    }
}

void DuckMarketPlace__preWithdrawInactiveCredit(DuckMarketPlace__IDUSUARIO uu, bool *oo)
{
    int32_t hasCredit;
    bool isInactive;
    bool hasDebit;
    
    hasCredit = DuckMarketPlace__usuariosinativos_i[uu];
    isInactive = DuckMarketPlace__usersInactive[uu];
    hasDebit = DuckMarketPlace__dividausuario_aberta_i[uu];
    if((((hasCredit) > (0)) &&
        (isInactive == true)) &&
    (hasDebit == false))
    {
        (*oo) = true;
    }
    else
    {
        (*oo) = false;
    }
}

void DuckMarketPlace__preRemoveInactiveUser(DuckMarketPlace__IDUSUARIO uu, bool *oo)
{
    int32_t hasCredit;
    bool isInactive;
    bool hasDebit;
    
    hasCredit = DuckMarketPlace__usuariosinativos_i[uu];
    isInactive = DuckMarketPlace__usersInactive[uu];
    hasDebit = DuckMarketPlace__dividausuario_aberta_i[uu];
    if((((hasCredit) <= (0)) &&
        (isInactive == true)) &&
    (hasDebit == false))
    {
        (*oo) = true;
    }
    else
    {
        (*oo) = false;
    }
}

