MACHINE
    DuckMarketPlace

SETS
    NOMEPRODUTO; NOMEUSUARIO; IDUSUARIO; IDPRODUTO
    
VARIABLES
    usuarios,
    creditousuario,
    usuariosinativos,
    dividausuario,
    userIdsUsed,

    produtos,
    estoque,
    precoproduto,
    
    dono,
    purchasedProducts,
    purchasedProductsCart,
    cartContents,
    totalPriceCart
    
INVARIANT
    usuarios : IDUSUARIO +-> NOMEUSUARIO &
    creditousuario : IDUSUARIO +-> NAT &
    usuariosinativos : IDUSUARIO +-> NAT &
    dividausuario : IDUSUARIO +-> NAT &
    
    produtos: IDPRODUTO +-> NOMEPRODUTO &
    estoque : IDPRODUTO +-> NAT & 
    precoproduto : IDPRODUTO +-> NAT & 
    
    dono : IDUSUARIO <-> IDPRODUTO & 
    purchasedProducts : IDUSUARIO <-> (IDPRODUTO <-> (NAT <-> NAT)) &
    purchasedProductsCart : IDUSUARIO <-> (IDPRODUTO <-> (NAT <-> NAT)) &
    cartContents : IDUSUARIO <-> (IDPRODUTO <-> (NAT <-> NAT)) &
    totalPriceCart : IDUSUARIO +-> NAT &

    userIdsUsed <: IDUSUARIO &
    dom(usuarios) <: userIdsUsed &
    dom(usuariosinativos) <: userIdsUsed &
    dom(dono) <: userIdsUsed &
    dom(creditousuario) <: userIdsUsed &

    dom(usuarios) /\ dom(usuariosinativos) = {} &
    dom(produtos) <: ran(dono)

INITIALISATION
    usuarios := {} ||
    creditousuario := {} ||
    usuariosinativos := {} ||
    dividausuario := {} ||
    userIdsUsed := {} ||

    produtos := {} ||
    estoque := {} ||
    precoproduto := {} ||
    
    dono := {} ||
    purchasedProducts := {} ||
    purchasedProductsCart := {} ||
    cartContents := {} ||
    totalPriceCart := {}

OPERATIONS

addUser(uu, nn, cc) =
    PRE uu : IDUSUARIO & nn : NOMEUSUARIO & cc : NAT &
        uu /: userIdsUsed 
    THEN 
        usuarios := usuarios \/ {uu |-> nn} ||
        creditousuario := creditousuario \/ {uu |-> cc} ||
	totalPriceCart := totalPriceCart \/ {uu |-> 0} ||

        userIdsUsed := userIdsUsed \/ {uu}
    END;
    
removeUser(uu) =
    PRE 
        uu : IDUSUARIO &
        uu : dom(usuarios) &
        uu : dom(creditousuario) &
        uu /: dom(dividausuario)
    THEN 
        usuarios := {uu} <<| usuarios ||
         
        produtos := dono[{uu}] <<| produtos ||
        estoque := dono[{uu}] <<| estoque ||
        precoproduto := dono[{uu}] <<| precoproduto ||
	 
        totalPriceCart := {uu} <<| totalPriceCart ||
        purchasedProducts := {uu} <<| purchasedProducts ||
	purchasedProductsCart := {uu} <<| purchasedProducts ||
        cartContents := {uu} <<| cartContents ||
         
         
        IF creditousuario(uu) > 0 THEN
            usuariosinativos := usuariosinativos \/ {uu |-> creditousuario(uu)}
        ELSE
            skip
        END ||
        creditousuario := {uu} <<| creditousuario
    END;

altNameUser(uu, nn) =
    PRE 
	uu : IDUSUARIO &
	uu : dom(usuarios) &
	nn : NOMEUSUARIO
    THEN usuarios := usuarios <+ {uu |-> nn}
    END;

addCredit(uu, cc) =
    PRE 
	uu: IDUSUARIO &
	cc : NAT1 &
	uu : dom(creditousuario) &
	(creditousuario(uu) + cc) : NAT1
    THEN creditousuario(uu) := creditousuario(uu) + cc
    END;
    
withdrawCredit(uu, cc) = 
    PRE 
        uu: IDUSUARIO &
        cc : NAT1 &
	uu : dom(creditousuario) &
	((creditousuario(uu) - cc) : NAT) &
	cc <= creditousuario(uu) &
	uu /: dom(dividausuario)
    THEN creditousuario := creditousuario <+ {uu |-> creditousuario(uu) - cc}
    END;

addProduct(ii, nn, uu) =
    PRE ii : IDPRODUTO & nn : NOMEPRODUTO &
	uu : IDUSUARIO & ii /: dom(produtos) &
	ii /: ran(dono) &
	uu : dom(usuarios)
    THEN produtos := produtos \/ {ii |-> nn} ||
         dono := dono \/ {uu |-> ii}
    END;

removeProduct(ii)=
   PRE ii : IDPRODUTO & ii : dom(produtos)
   THEN produtos := {ii} <<| produtos ||
        dono := dono |>> {ii} ||
        estoque := {ii} <<| estoque ||
        precoproduto := {ii} <<| precoproduto
   END;

altProductName(ii, nn) =
    PRE ii : IDPRODUTO & ii : dom(produtos) & nn : NOMEPRODUTO
    THEN produtos := produtos <+ {ii |-> nn}
    END;

altProductStock(ii, qq) =
    PRE ii : IDPRODUTO & ii : dom(produtos) & qq : NAT
    THEN estoque := estoque <+ {ii |-> qq}
    END;

altProductPrice(ii, pp) =
    PRE ii : IDPRODUTO & ii : dom(produtos) & pp : NAT1
    THEN precoproduto := precoproduto <+ {ii |-> pp}
    END;

buyProduct(uu, pp, qq) =
    PRE
      uu : IDUSUARIO & 
      pp : IDPRODUTO & 
      uu : dom(usuarios) & 
      pp : dom(produtos) &
      uu /= dono~(pp) &
      qq : NAT1 &
      precoproduto(pp) * qq <= creditousuario(uu) &
      qq <= estoque(pp) 
    THEN 
      IF uu /: dom(purchasedProducts) THEN
          purchasedProducts(uu) := {pp |-> {precoproduto(pp) |-> qq}}
      ELSE
          IF pp : dom(purchasedProducts(uu)) THEN
              IF precoproduto(pp) : dom(purchasedProducts(uu)(pp)) THEN
                  purchasedProducts(uu)(pp)(precoproduto(pp)) := purchasedProducts(uu)(pp)(precoproduto(pp)) + qq
              ELSE
                  purchasedProducts(uu)(pp) := purchasedProducts(uu)(pp) \/ {precoproduto(pp) |-> qq}
              END
          ELSE
              purchasedProducts(uu) := purchasedProducts(uu) \/ {pp |-> {precoproduto(pp) |-> qq}}
          END
      END ||
      creditousuario := creditousuario <+ {
          uu |-> (creditousuario(uu) - (precoproduto(pp) * qq)),
          dono~(pp) |-> (creditousuario(dono~(pp)) + (precoproduto(pp) * qq))
      } ||
      estoque(pp) := estoque(pp) - qq
    END;


returnProduct(uu, pp, rr, qq) =
  PRE
    uu : IDUSUARIO &
    uu : dom(purchasedProducts) &
    pp : dom(purchasedProducts(uu)) &
    rr : NAT &
    qq : NAT1 &
    rr : dom(purchasedProducts(uu)(pp)) &
    qq <= purchasedProducts(uu)(pp)(rr)
  THEN
    IF dono~(pp) : dom(dividausuario) THEN
        dividausuario(dono~(pp)) := dividausuario(dono~(pp)) + (purchasedProducts(uu)(pp)(rr) * rr)
    ELSE
        dividausuario := dividausuario \/ {dono~(pp) |-> purchasedProducts(uu)(pp)(rr) * rr}
    END ||
    creditousuario(uu) := creditousuario(uu) + purchasedProducts(uu)(pp)(rr) * rr ||
    IF qq = purchasedProducts(uu)(pp)(rr) THEN
      IF card(purchasedProducts(uu)(pp)) <= 1 THEN
           purchasedProducts(uu) := {pp} <<| purchasedProducts(uu)
      ELSE
          purchasedProducts(uu)(pp) := {rr} <<| purchasedProducts(uu)(pp)
      END
    ELSE
      purchasedProducts(uu)(pp)(rr) := purchasedProducts(uu)(pp)(rr) - qq
    END
    ||
    IF pp : dom(estoque) THEN
        estoque := estoque <+ {
          pp |-> estoque(pp) + qq
        }
    ELSE
        skip
    END
  END;

addProductToCart(uu, pp, qq) =
    PRE
      uu : IDUSUARIO & 
      pp : IDPRODUTO & 
      uu : dom(usuarios) & 
      pp : dom(produtos) &
      uu /= dono~(pp) &
      qq : NAT1 &
      uu : dom(totalPriceCart) &
      precoproduto(pp) * qq <= creditousuario(uu) &
      qq <= estoque(pp) 
    THEN 
      IF uu /: dom(cartContents) THEN
          cartContents(uu) := {pp |-> {precoproduto(pp) |-> qq}}
      ELSE
          IF pp : dom(cartContents(uu)) THEN
              IF precoproduto(pp) : dom(cartContents(uu)(pp)) THEN
                  cartContents(uu)(pp)(precoproduto(pp)) := cartContents(uu)(pp)(precoproduto(pp)) + qq
              ELSE
                  cartContents(uu)(pp) := cartContents(uu)(pp) \/ {precoproduto(pp) |-> qq}
              END
          ELSE
              cartContents(uu) := cartContents(uu) \/ {pp |-> {precoproduto(pp) |-> qq}}
          END
      END ||
      totalPriceCart(uu) := totalPriceCart(uu) + (precoproduto(pp)*qq) ||
      estoque(pp) := estoque(pp) - qq
    END;

removeProductFromCart(uu, pp, rr, qq) =
  PRE
    uu : IDUSUARIO &
    uu : dom(cartContents) &
    pp : dom(cartContents(uu)) &
    rr : NAT &
    qq : NAT1 &
    rr : dom(cartContents(uu)(pp)) &
    qq <= cartContents(uu)(pp)(rr)
  THEN
   IF qq = cartContents(uu)(pp)(rr) THEN
      totalPriceCart(uu) := totalPriceCart(uu) - (cartContents(uu)(pp)(rr) * rr) ||
      IF card(cartContents(uu)(pp)) <= 1 THEN
           cartContents(uu) := {pp} <<| cartContents(uu)
      ELSE
          cartContents(uu)(pp) := {rr} <<| cartContents(uu)(pp)
      END
   ELSE
      totalPriceCart(uu) := totalPriceCart(uu) - (qq * rr) ||
      cartContents(uu)(pp)(rr) := cartContents(uu)(pp)(rr) - qq
   END
    ||
    IF pp : dom(estoque) THEN
        estoque := estoque <+ {
          pp |-> estoque(pp) + qq
        }
    ELSE
        skip
    END
  END;

buyProductsFromCart(uu) =
    PRE uu : IDUSUARIO & uu : dom(cartContents) &
        uu : dom(creditousuario) &
	uu : dom(totalPriceCart) &
        creditousuario(uu) >= totalPriceCart(uu)
    THEN
	creditousuario(uu) := creditousuario(uu) - totalPriceCart(uu) ||
	totalPriceCart(uu) := 0 ||
	cartContents := {uu} <<| cartContents ||
	IF uu : dom(purchasedProductsCart) THEN
	    purchasedProductsCart(uu) := purchasedProductsCart(uu) \/ cartContents(uu)
	ELSE
	    purchasedProductsCart := purchasedProductsCart \/ {uu |-> cartContents(uu)}
	END
	
    END;

returnProductBuyedCart(uu, pp, rr, qq) =
  PRE
    uu : IDUSUARIO &
    uu : dom(purchasedProductsCart) &
    pp : dom(purchasedProductsCart(uu)) &
    rr : NAT &
    qq : NAT1 &
    rr : dom(purchasedProductsCart(uu)(pp)) &
    qq <= purchasedProductsCart(uu)(pp)(rr)
  THEN
    IF dono~(pp) : dom(dividausuario) THEN
        dividausuario(dono~(pp)) := dividausuario(dono~(pp)) + (purchasedProductsCart(uu)(pp)(rr) * rr)
    ELSE
        dividausuario := dividausuario \/ {dono~(pp) |-> purchasedProductsCart(uu)(pp)(rr) * rr}
    END ||
    creditousuario(uu) := creditousuario(uu) + purchasedProductsCart(uu)(pp)(rr) * rr ||
    IF qq = purchasedProductsCart(uu)(pp)(rr) THEN
      IF card(purchasedProductsCart(uu)(pp)) <= 1 THEN
           purchasedProductsCart(uu) := {pp} <<| purchasedProductsCart(uu)
      ELSE
          purchasedProducts(uu)(pp) := {rr} <<| purchasedProducts(uu)(pp)
      END
    ELSE
      purchasedProducts(uu)(pp)(rr) := purchasedProducts(uu)(pp)(rr) - qq
    END
    ||
    IF pp : dom(estoque) THEN
        estoque := estoque <+ {
          pp |-> estoque(pp) + qq
        }
    ELSE
        skip
    END
  END;

payDebt(ii) = 
    PRE 
        ii : IDUSUARIO &
        ii : dom(dividausuario) &
        ii : dom(usuarios) &
        ii : dom(creditousuario)
    THEN
        IF creditousuario(ii) >= dividausuario(ii) THEN
            creditousuario(ii) := creditousuario(ii) - dividausuario(ii) ||
	    dividausuario := {ii} <<| dividausuario
        ELSE
            dividausuario(ii) := dividausuario(ii) - creditousuario(ii) ||
	    creditousuario(ii) := 0
	END
    END;

payDebtWithCredit(ii, cc) =
    PRE
        ii : IDUSUARIO &
        ii : dom(dividausuario) &
        cc : NAT1
    THEN
        IF cc >= dividausuario(ii) THEN
            dividausuario := {ii} <<| dividausuario
        ELSE
            dividausuario(ii) := dividausuario(ii) - cc
        END
    END;
    
withdrawInactiveCredit(uu) =
    PRE uu : IDUSUARIO & uu : dom(usuariosinativos) &
	uu /: dom(dividausuario)
    THEN 
        usuariosinativos := usuariosinativos <+ {uu |-> 0}
    END;
    
removeInactiveUser(uu) =
    PRE uu : IDUSUARIO & uu : dom(usuariosinativos) & usuariosinativos(uu) <= 0
    THEN 
        usuariosinativos := {uu} <<| usuariosinativos
    END;

// Operações de query
oo <-- showUserCredit(uu) =
	oo := creditousuario(uu);

oo <-- showUserCartValue(uu) =
	oo := totalPriceCart(uu);

oo <-- showUserDebt(uu) =
	oo := dividausuario(uu)


END