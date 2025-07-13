MACHINE DuckMarketPlace

SETS
    NOMEPRODUTO; NOMEUSUARIO; IDUSUARIO; IDPRODUTO

CONSTANTS
    userDummy, productDummy, userIdDummy, productIdDummy, MAX_PURCHASE
    
PROPERTIES
    userDummy:NOMEUSUARIO &
    productDummy:NOMEPRODUTO &
    userIdDummy:IDUSUARIO &
    productIdDummy : IDPRODUTO &
    MAX_PURCHASE = 15
    
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

    cartContents,
    totalPriceCart,
    cartSeller,
    idPurchase,
    lastPurchase,
    purchaseUsers,
    purchaseHistory
    
INVARIANT
    usuarios : IDUSUARIO +-> NOMEUSUARIO &
    creditousuario : IDUSUARIO +-> NAT &
    usuariosinativos : IDUSUARIO +-> NAT &
    dividausuario : IDUSUARIO +-> NAT &
    userIdsUsed <: IDUSUARIO &
    
    produtos: IDPRODUTO +-> NOMEPRODUTO &
    estoque : IDPRODUTO +-> NAT & 
    precoproduto : IDPRODUTO +-> NAT & 
    dono : IDPRODUTO +-> IDUSUARIO & 

    // Itens do carrinho de um usuário (NAT <-> NAT = preço do produto <-> quantidade do produto)
    cartContents : IDUSUARIO +-> (IDPRODUTO +-> (NAT <-> NAT)) &
    // Preço total do carrinho de um usuário
    totalPriceCart : IDUSUARIO +-> NAT &
    // Vendedor dos produtos do carrinho de um usuário
    cartSeller : IDUSUARIO +-> IDUSUARIO &
    // Armazena a última compra de um usuário
    lastPurchase : IDUSUARIO +-> (IDPRODUTO +-> (NAT <-> NAT)) &
    // Armazena Os ids das compras de um usuário
    purchaseUsers : 0..MAX_PURCHASE +-> IDUSUARIO & 
    // Histórico das compras dos usuários
    purchaseHistory : 0..MAX_PURCHASE  +-> (IDPRODUTO <-> (NAT <-> NAT)) &
    // O ID da próxima compra
    idPurchase : 0..MAX_PURCHASE  &

    // Invariants de MAXINT
    !cc.(cc : ran(creditousuario) => cc <= MAXINT) &
    !cc.(cc : ran(usuariosinativos) => cc <= MAXINT) &
    !cc.(cc : ran(dividausuario) => cc <= MAXINT) &

    !pp.(pp : ran(estoque) => pp <= MAXINT) &
    !pp.(pp : ran(precoproduto) => pp <= MAXINT) &

    !bb.(bb : ran(totalPriceCart) => bb <= MAXINT) &
    
    // Invariants de conjuntos
    dom(usuarios) <: userIdsUsed &
    dom(usuariosinativos) <: userIdsUsed &
    ran(dono) <: userIdsUsed &
    dom(creditousuario) <: userIdsUsed &

    dom(usuarios) /\ dom(usuariosinativos) = {} &
    dom(produtos) <: dom(dono)

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

    cartContents := {} ||
    totalPriceCart := {} ||
    idPurchase := 0 ||
    lastPurchase := {} ||
    purchaseUsers := {} ||
    purchaseHistory := {} ||
    cartSeller := {}

OPERATIONS

addUser(uu, nn, cc) =
    PRE 
	uu : IDUSUARIO &
	nn : NOMEUSUARIO &
	cc : NAT &
	cc <= MAXINT &
        uu /: userIdsUsed &
	uu /: dom(totalPriceCart) &
	uu /= userIdDummy &
	nn /= userDummy
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
         
        produtos := dom(dono |> {uu}) <<| produtos ||
        estoque := dom(dono |> {uu}) <<| estoque ||
        precoproduto := dom(dono |> {uu}) <<| precoproduto ||
	 
        totalPriceCart := {uu} <<| totalPriceCart ||
        purchaseHistory := ( dom( purchaseUsers |> {uu} ) ) <<| purchaseHistory || 
	purchaseUsers := purchaseUsers |>> {uu} ||
        cartContents := {uu} <<| cartContents ||
	lastPurchase := {uu} <<| lastPurchase ||
	cartSeller := {uu} <<| cartSeller ||
         
         
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
	nn : NOMEUSUARIO &
	nn /= userDummy
    THEN usuarios := usuarios <+ {uu |-> nn}
    END;

addCredit(uu, cc) =
    PRE 
	uu: IDUSUARIO &
	cc : NAT &
	cc > 0 &
	cc <= MAXINT &
	uu : dom(creditousuario) &
	(creditousuario(uu) + cc) <= MAXINT
    THEN creditousuario(uu) := creditousuario(uu) + cc
    END;
    
withdrawCredit(uu, cc) = 
    PRE 
        uu: IDUSUARIO &
        cc : NAT &
	cc > 0 &
	cc <= MAXINT &
	uu : dom(creditousuario) &
	((creditousuario(uu) - cc) : NAT) &
	cc <= creditousuario(uu) &
	uu /: dom(dividausuario)
    THEN creditousuario := creditousuario <+ {uu |-> creditousuario(uu) - cc}
    END;

addProduct(ii, nn, uu, qq, pp) =
    PRE 
	ii : IDPRODUTO &
	nn : NOMEPRODUTO &
	uu : IDUSUARIO &
	ii /: dom(produtos) &
	qq: NAT &
	qq <= MAXINT &
	pp : NAT &
	pp <= MAXINT &
	ii /: dom(dono) &
	uu : dom(usuarios) &
	nn /= productDummy &
	uu /= userIdDummy &
	ii /= productIdDummy
    THEN produtos := produtos \/ {ii |-> nn} ||
         dono := dono \/ {ii |-> uu} ||
	 estoque := estoque \/ {ii |-> qq} ||
         precoproduto := precoproduto \/ {ii |-> pp}
    END;

removeProduct(ii)=
   PRE ii : IDPRODUTO & ii : dom(produtos) & ii : dom(precoproduto) & ii : dom(estoque) & ii : dom(dono)
   THEN produtos := {ii} <<| produtos ||
	dono := {ii} <<| dono ||
        estoque := {ii} <<| estoque ||
        precoproduto := {ii} <<| precoproduto
   END;

altProductName(ii, nn) =
    PRE 
	ii : IDPRODUTO &
	ii : dom(produtos) &
	nn : NOMEPRODUTO &
	nn /= productDummy &
	ii /= productIdDummy
    THEN produtos := produtos <+ {ii |-> nn}
    END;

altProductStock(ii, qq) =
    PRE 
	ii : IDPRODUTO &
	ii : dom(produtos) &
	qq : NAT &
	qq <= MAXINT &
	qq > 0 &
	ii /= productIdDummy
    THEN estoque := estoque <+ {ii |-> qq}
    END;

altProductPrice(ii, pp) =
    PRE 
	ii : IDPRODUTO &
	ii : dom(produtos) &
	pp : NAT &
	pp <= MAXINT &
	pp > 0 &
	ii /= productIdDummy
    THEN precoproduto := precoproduto <+ {ii |-> pp}
    END;

buyProduct(uu, pp, qq) =
    PRE
      uu : IDUSUARIO & 
      pp : IDPRODUTO &
      qq : NAT & 
      uu : dom(usuarios) & 
      pp : dom(produtos) &
      uu /= dono(pp) &
      qq > 0 &
      qq <= MAXINT &
      ( creditousuario(dono(pp)) + (precoproduto(pp) * qq) ) <= MAXINT &
      precoproduto(pp) * qq <= creditousuario(uu) &
      qq <= estoque(pp)  &
      card(purchaseUsers) < MAX_PURCHASE &
      card(purchaseHistory) < MAX_PURCHASE  &
      idPurchase < MAX_PURCHASE
    THEN
        lastPurchase(uu) := {pp |-> {precoproduto(pp) |-> qq}} ||
        purchaseUsers := purchaseUsers \/ {idPurchase |-> uu} ||
        purchaseHistory := purchaseHistory \/ {idPurchase |-> {pp |-> {precoproduto(pp) |-> qq}}} ||
	idPurchase := idPurchase + 1 ||
         
        creditousuario := creditousuario <+ {
            uu |-> (creditousuario(uu) - (precoproduto(pp) * qq)),
             dono(pp) |-> (creditousuario(dono(pp)) + (precoproduto(pp) * qq))
        } ||
        estoque(pp) := estoque(pp) - qq 
    END;

returnProduct(uu, pp, rr, qq) =
  PRE
    uu : IDUSUARIO &
    uu : dom(lastPurchase) &
    pp : IDPRODUTO &
    pp : dom(lastPurchase(uu)) &
    rr : NAT &
    rr <= MAXINT &
    qq : NAT &
    qq > 0 &
    qq <= MAXINT &
    rr : dom(lastPurchase(uu)(pp)) &
    qq <= lastPurchase(uu)(pp)(rr) &
    (pp : dom(estoque) => ( qq + estoque(pp) ) <= MAXINT) &
    ( creditousuario(uu) + lastPurchase(uu)(pp)(rr) * rr ) <= MAXINT &
    ( dono(pp) : dom(dividausuario) =>
	( dividausuario(dono(pp)) + (lastPurchase(uu)(pp)(rr) * rr) ) <= MAXINT ) &
    ( dono(pp) /: dom(dividausuario) => (lastPurchase(uu)(pp)(rr) * rr) <= MAXINT )
  THEN
    IF dono(pp) : dom(dividausuario) THEN
        dividausuario(dono(pp)) := dividausuario(dono(pp)) + (qq * rr)
    ELSE
        dividausuario := dividausuario \/ {dono(pp) |-> qq * rr}
    END ||
    creditousuario(uu) := creditousuario(uu) + qq * rr ||
    IF qq = lastPurchase(uu)(pp)(rr) THEN
      IF card(lastPurchase(uu)(pp)) <= 1 THEN
           lastPurchase(uu) := {pp} <<| lastPurchase(uu) ||
           purchaseHistory(max( dom(purchaseUsers |> {uu}) )) := {pp} <<| lastPurchase(uu)
      ELSE
          lastPurchase(uu)(pp) := {rr} <<| lastPurchase(uu)(pp) ||
          purchaseHistory( max( dom(purchaseUsers |> {uu}) ) )(pp) := {rr} <<| purchaseHistory( max( dom(purchaseUsers |> {uu}) ) )(pp)
      END
    ELSE
      lastPurchase(uu)(pp)(rr) := lastPurchase(uu)(pp)(rr) - qq ||
      purchaseHistory(max( dom(purchaseUsers |> {uu}) ))(pp)(rr) := purchaseHistory( max( dom(purchaseUsers |> {uu}) ) )(pp)(rr) -qq
    END
    ||
    IF pp : dom(estoque) THEN
        estoque := estoque <+ {
          pp |-> estoque(pp) + qq
        }
    END
  END;


addProductToCart(uu, pp, qq) =
    PRE
      uu : IDUSUARIO & 
      pp : IDPRODUTO & 
      uu : dom(usuarios) & 
      pp : dom(produtos) &
      uu /= dono(pp) &
      qq : NAT &
      qq > 0 &
      qq <= MAXINT &
      uu : dom(totalPriceCart)  &
      qq <= estoque(pp) &
      ( uu : dom(cartContents) &  pp : dom(cartContents(uu)) & precoproduto(pp) : dom(cartContents(uu)(pp)) => (cartContents(uu)(pp)(precoproduto(pp)) + qq) <= MAXINT )&
      (uu /: dom(cartSeller) or cartSeller(uu) = dono(pp)) &
      ( uu : dom(totalPriceCart) => ( totalPriceCart(uu) + (precoproduto(pp)*qq) ) <= MAXINT )
    THEN
      IF uu /: dom(cartSeller) THEN
	cartSeller := cartSeller \/ {uu |-> dono(pp)}
      END ||

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
    pp : IDPRODUTO &
    uu : dom(cartContents) &
    pp : dom(cartContents(uu)) &
    rr : NAT &
    rr <= MAXINT &
    qq : NAT &
    qq > 0 &
    qq <= MAXINT &
    rr : dom(cartContents(uu)(pp)) &
    qq <= cartContents(uu)(pp)(rr) &
    ( pp : dom(estoque) => (qq + estoque(pp)) <= MAXINT)
  THEN
   IF qq = cartContents(uu)(pp)(rr) THEN
      totalPriceCart(uu) := totalPriceCart(uu) - (cartContents(uu)(pp)(rr) * rr) ||
      IF card(cartContents(uu)(pp)) <= 1 THEN
           cartContents(uu) := {pp} <<| cartContents(uu) ||
	   IF dom(cartContents(uu)) = {pp} THEN
		cartSeller := {uu} <<| cartSeller
	   END
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
    PRE 
	uu : IDUSUARIO &
	uu : dom(cartContents) &
        uu : dom(creditousuario) &
	uu : dom(totalPriceCart) &
        creditousuario(uu) >= totalPriceCart(uu) &
        ( (idPurchase + 1) <= MAXINT ) &
	uu : dom(cartSeller) &
	cartSeller(uu) : dom(creditousuario) &
	creditousuario(cartSeller(uu)) + totalPriceCart(uu) <= MAXINT &
	card(purchaseUsers) < MAX_PURCHASE &
	card(purchaseHistory) < MAX_PURCHASE   &
        idPurchase < MAX_PURCHASE
    THEN
	creditousuario := creditousuario <+ {
            uu |-> (creditousuario(uu) - totalPriceCart(uu) ),
             cartSeller(uu) |-> (creditousuario(cartSeller(uu)) + totalPriceCart(uu))
        } || 
	totalPriceCart(uu) := 0 ||
	cartContents := {uu} <<| cartContents ||
        
        lastPurchase(uu) := cartContents(uu) ||
        purchaseUsers := purchaseUsers \/ {idPurchase |-> uu} ||
        purchaseHistory := purchaseHistory \/ {idPurchase |-> cartContents(uu)} ||
	idPurchase := idPurchase + 1 ||
	cartSeller := {uu} <<| cartSeller	
    END;

payDebt(uu) = 
    PRE 
        uu : IDUSUARIO &
        uu : dom(dividausuario) &
        uu : dom(usuarios) &
        uu : dom(creditousuario)
    THEN
        IF creditousuario(uu) >= dividausuario(uu) THEN
            creditousuario(uu) := creditousuario(uu) - dividausuario(uu) ||
	    dividausuario := {uu} <<| dividausuario
        ELSE
            dividausuario(uu) := dividausuario(uu) - creditousuario(uu) ||
	    creditousuario(uu) := 0
	END
    END;

payDebtWithCredit(uu, cc) =
    PRE
        uu : IDUSUARIO &
        uu : dom(dividausuario) &
        cc : NAT &
        cc > 0 &
        cc <= MAXINT &
	cc <= dividausuario(uu)
    THEN
        IF cc >= dividausuario(uu) THEN
            dividausuario := {uu} <<| dividausuario
        ELSE
            dividausuario(uu) := dividausuario(uu) - cc
        END
    END;
    
withdrawInactiveCredit(uu) =
    PRE 
	uu : IDUSUARIO &
	uu : dom(usuariosinativos) &
	uu /: dom(dividausuario) &
	usuariosinativos(uu) > 0
    THEN 
        usuariosinativos := usuariosinativos <+ {uu |-> 0}
    END;
    
removeInactiveUser(uu) =
    PRE 
	uu : IDUSUARIO &
	uu : dom(usuariosinativos) &
	usuariosinativos(uu) <= 0 &
	uu /: dom(dividausuario)
    THEN 
        usuariosinativos := {uu} <<| usuariosinativos
    END;

/* ----- Operações de query ----- */
oo <-- showUserCredit(uu) =
    PRE uu : IDUSUARIO & uu : dom(creditousuario)
    THEN
	oo := creditousuario(uu)
    END;

oo <-- showUserName(uu) =
    PRE uu : IDUSUARIO & uu : dom(usuarios)
    THEN
	oo := usuarios(uu)
    END;

oo <-- showUserCartValue(uu) =
    PRE uu : IDUSUARIO & uu : dom(totalPriceCart)
    THEN
	oo := totalPriceCart(uu)
    END;

oo <-- showUserDebt(uu) =
    PRE uu : IDUSUARIO & uu : dom(dividausuario)
    THEN
	oo := dividausuario(uu)
    END;

oo <-- showProductName(pp) =
    PRE pp : IDPRODUTO & pp : dom(produtos)
    THEN
	oo := produtos(pp)
    END;

oo <-- showProductStock(pp) =
    PRE pp : IDPRODUTO & pp : dom(estoque)
    THEN
	oo := estoque(pp)
    END;

oo <-- showProductPrice(pp) =
    PRE pp : IDPRODUTO & pp : dom(precoproduto)
    THEN
	oo := precoproduto(pp)
    END;

/* ----- Operações de pré condições ----- */
oo <-- preAddUser(uu, nn, cc) =
    PRE uu : IDUSUARIO & nn : NOMEUSUARIO & cc : NAT THEN
	IF
	    cc <= MAXINT &
	    uu /: userIdsUsed &
	    uu /: dom(totalPriceCart) &
	    uu /= userIdDummy &
	    nn /= userDummy
	THEN
	    oo := TRUE
	ELSE
	    oo := FALSE
	END      
    END;

oo <-- preRemoveUser(uu) =
    PRE uu : IDUSUARIO THEN
	IF uu : dom(usuarios) &
           uu : dom(creditousuario) &
           uu /: dom(dividausuario)
	THEN oo := TRUE
	ELSE oo := FALSE
	END
    END;

oo <-- preAltNameUser(uu, nn) =
    PRE uu : IDUSUARIO & nn : NOMEUSUARIO THEN
	IF uu : dom(usuarios) & nn /= userDummy THEN
	    oo := TRUE
	ELSE 
	    oo := FALSE
	END
    END;

oo <-- preAddCredit(uu, cc) =
    PRE uu: IDUSUARIO & cc : NAT THEN
	IF 
	    uu : dom(creditousuario) &
	    (creditousuario(uu) + cc) <= MAXINT &
	    cc > 0 &
	    cc <= MAXINT
	THEN oo := TRUE
	ELSE oo := FALSE
	END
    END;


oo <-- preWithdrawCredit(uu, cc) = 
    PRE uu: IDUSUARIO & cc : NAT THEN
	IF 
	    cc > 0 &
	    cc <= MAXINT &
	    uu : dom(creditousuario) &
	    ((creditousuario(uu) - cc) : NAT) &
	    cc <= creditousuario(uu) &
	    uu /: dom(dividausuario)
	THEN oo := TRUE
	ELSE oo := FALSE
	END
    END;

oo <-- preAddProduct(ii, nn, uu, qq, pp) =
    PRE ii : IDPRODUTO & nn : NOMEPRODUTO & uu : IDUSUARIO &
	qq : NAT & pp : NAT
    THEN
	IF
	    qq <= MAXINT &
	    pp <= MAXINT &
	    ii /: dom(produtos) &
	    ii /: dom(dono) &
	    uu : dom(usuarios) &
	    nn /= productDummy &
	    uu /= userIdDummy &
	    ii /= productIdDummy
	THEN oo := TRUE
	ELSE oo := FALSE
	END
    END;

oo <-- preRemoveProduct(ii) =
   PRE ii : IDPRODUTO THEN 
	IF ii : dom(produtos) THEN
	    oo := TRUE
	ELSE oo := FALSE
	END
   END;

oo <-- preAltProductName(ii, nn) =
    PRE ii : IDPRODUTO & nn : NOMEPRODUTO THEN
	IF ii : dom(produtos) & nn /= productDummy & ii /= productIdDummy THEN
	    oo := TRUE
	ELSE oo := FALSE
	END
    END;

oo <-- preAltProductStock(ii, qq) =
    PRE ii : IDPRODUTO & qq : NAT THEN
	IF ii : dom(produtos) & qq <= MAXINT & ii /= productIdDummy & qq > 0 THEN
	    oo := TRUE
	ELSE oo := FALSE
	END
    END;

oo <-- preAltProductPrice(ii, pp) =
    PRE ii : IDPRODUTO & pp : NAT THEN
	IF ii : dom(produtos) & pp <= MAXINT & ii /= productIdDummy & pp > 0 THEN
	    oo := TRUE
	ELSE oo := FALSE
	END
    END;

oo <-- preBuyProduct(uu, pp, qq) =
    PRE uu : IDUSUARIO & pp : IDPRODUTO & qq : NAT
    THEN
        IF  uu : dom(usuarios) & 
      	    pp : dom(produtos) &
      	    uu /= dono(pp) &
      	    qq > 0 &
      	    qq <= MAXINT &
	    ( creditousuario(dono(pp)) + (precoproduto(pp) * qq) ) <= MAXINT &
      	    precoproduto(pp) * qq <= creditousuario(uu) &
      	    qq <= estoque(pp) &
	    card(purchaseUsers) < MAX_PURCHASE &
            card(purchaseHistory) < MAX_PURCHASE &
	    idPurchase < MAX_PURCHASE &
	    pp /= productIdDummy &
	    uu /= userIdDummy
	THEN oo := TRUE
	ELSE oo := FALSE
	END
    END;

oo <-- preReturnProduct(uu, pp, rr, qq) =
  PRE
    uu : IDUSUARIO &
    pp : IDPRODUTO &
    rr : NAT &
    qq : NAT
  THEN
    IF  uu : dom(lastPurchase) &
        pp : dom(lastPurchase(uu)) &
	rr <= MAXINT &
    	qq > 0 &
    	qq <= MAXINT &
        rr : dom(lastPurchase(uu)(pp)) &
        qq <= lastPurchase(uu)(pp)(rr) &
	(pp : dom(estoque) => ( qq + estoque(pp) ) <= MAXINT) &
        ( creditousuario(uu) + lastPurchase(uu)(pp)(rr) * rr ) <= MAXINT &
        ( dono(pp) : dom(dividausuario) =>
	( dividausuario(dono(pp)) + (lastPurchase(uu)(pp)(rr) * rr) ) <= MAXINT ) &
        ( dono(pp) /: dom(dividausuario) => (lastPurchase(uu)(pp)(rr) * rr) <= MAXINT )
    THEN oo := TRUE
    ELSE oo := FALSE
    END
  END;

oo <-- preAddProductToCart(uu, pp, qq) =
    PRE uu : IDUSUARIO & pp : IDPRODUTO & qq : NAT THEN
       IF 
	  uu : dom(usuarios) & 
          pp : dom(produtos) &
          uu /= dono(pp) &
          qq > 0 &
          qq <= MAXINT &
          uu : dom(totalPriceCart) &
          qq <= estoque(pp) &
          ( uu : dom(cartContents) &  pp : dom(cartContents(uu)) & precoproduto(pp) : dom(cartContents(uu)(pp)) => (cartContents(uu)(pp)(precoproduto(pp)) + qq) <= MAXINT )&
          (uu /: dom(cartSeller) or cartSeller(uu) = dono(pp)) &
          ( uu : dom(totalPriceCart) => ( totalPriceCart(uu) + (precoproduto(pp)*qq) ) <= MAXINT )
	THEN oo := TRUE
        ELSE oo := FALSE
        END
    END;

oo <-- preRemoveProductFromCart(uu, pp, rr, qq) =
  PRE
    uu : IDUSUARIO &
    pp : IDPRODUTO &
    rr : NAT &
    qq : NAT
  THEN
    IF 
	uu : dom(cartContents) &
       	pp : dom(cartContents(uu)) &
       	rr <= MAXINT &
    	qq > 0 &
    	qq <= MAXINT &
       	rr : dom(cartContents(uu)(pp)) &
       	qq <= cartContents(uu)(pp)(rr) & 
      	( pp : dom(estoque) => (qq + estoque(pp)) <= MAXINT)
    THEN oo := TRUE
    ELSE oo := FALSE
    END
  END;

oo <-- preBuyProductsFromCart(uu) =
    PRE uu : IDUSUARIO THEN
	IF uu : dom(cartContents) &
           uu : dom(creditousuario) &
	   uu : dom(totalPriceCart) &
           creditousuario(uu) >= totalPriceCart(uu) &
	   ( (idPurchase + 1) <= MAXINT ) &
	   uu : dom(cartSeller) &
	   cartSeller(uu) : dom(creditousuario) &
	   creditousuario(cartSeller(uu)) + totalPriceCart(uu) <= MAXINT &
	   card(purchaseUsers) < MAX_PURCHASE &
	   card(purchaseHistory) < MAX_PURCHASE   &
           idPurchase < MAX_PURCHASE
	THEN oo := TRUE
        ELSE oo := FALSE
        END
    END;

oo <-- prePayDebt(uu) = 
    PRE uu : IDUSUARIO THEN
        IF
            uu : dom(dividausuario) &
            uu : dom(usuarios) &
            uu : dom(creditousuario)
	THEN oo := TRUE
        ELSE oo := FALSE
        END
    END;

oo <-- prePayDebtWithCredit(uu, cc) =
    PRE uu : IDUSUARIO & cc : NAT THEN
        IF 
	    uu : dom(dividausuario) &
	    cc > 0 &
            cc <= MAXINT &
	    cc <= dividausuario(uu) 
	THEN
	    oo := TRUE
	ELSE oo := FALSE
        END
    END;
    
oo <-- preWithdrawInactiveCredit(uu) =
    PRE uu : IDUSUARIO THEN 
        IF 
	    uu : dom(usuariosinativos) &
	    uu /: dom(dividausuario) &
	    usuariosinativos(uu) > 0
	THEN oo := TRUE
        ELSE oo := FALSE
        END
    END;
    
oo <-- preRemoveInactiveUser(uu) =
    PRE uu : IDUSUARIO THEN 
        IF 
	    uu : dom(usuariosinativos) &
	    usuariosinativos(uu) <= 0 &
	    uu /: dom(dividausuario)
	THEN oo := TRUE
        ELSE oo := FALSE
        END
    END

END