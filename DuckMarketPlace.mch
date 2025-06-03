MACHINE
    DuckMarketPlace

SETS
    NOMEPRODUTO; NOMEUSUARIO; IDUSUARIO; IDPRODUTO
    
VARIABLES
    usuarios, creditousuario, usuariosinativos,
    produtos, estoque, precoproduto, dono, cartcontents,
    dividausuario
    
INVARIANT
    usuarios : IDUSUARIO <-> NOMEUSUARIO &
    creditousuario : IDUSUARIO <-> NAT &
    produtos: IDPRODUTO <-> NOMEPRODUTO &
    estoque : IDPRODUTO <-> NAT & 
    precoproduto : IDPRODUTO <-> NAT & 
    dono : IDUSUARIO <-> IDPRODUTO &
    cartcontents : IDUSUARIO <-> (IDPRODUTO <-> (NAT <-> NAT)) &
    
    usuariosinativos : IDUSUARIO <-> NAT &
    dividausuario : IDUSUARIO <-> NAT &

    dom(usuarios) /\ dom(usuariosinativos) = {} &
    dom(produtos) /\ ran(dono) = {}

INITIALISATION
    usuarios := {} || creditousuario := {} || usuariosinativos := {} ||
    produtos := {} || estoque := {} || precoproduto := {} || dono := {} ||
    cartcontents := {} || dividausuario := {}

OPERATIONS

addUser(ii, nn, cc) =
    PRE ii : IDUSUARIO & nn : NOMEUSUARIO & cc : NAT &
        ii /: dom(usuarios) & ii /: dom(creditousuario) &
	ii /: dom(dono) &
	ii /: dom(usuariosinativos)
    THEN usuarios := usuarios \/ {ii |-> nn} ||
         creditousuario := creditousuario \/ {ii |-> cc}
    END;
    
removeUser(ii) =
    PRE 
        ii : IDUSUARIO &
        ii : dom(usuarios) &
        ii : dom(creditousuario) &
        ii /: dom(dividausuario)
    THEN usuarios := {ii} <<| usuarios ||
         cartcontents := {ii} <<| cartcontents ||
         
         produtos := dono[{ii}] <<| produtos ||
         estoque := dono[{ii}] <<| estoque ||
         precoproduto := dono[{ii}] <<| precoproduto ||
         
         
         IF creditousuario(ii) > 0 THEN
             usuariosinativos := usuariosinativos \/ {ii |-> creditousuario(ii)}
         ELSE
             skip
         END ||
         creditousuario := {ii} <<| creditousuario
    END;

altNameUser(ii, nn) =
    PRE ii : IDUSUARIO & ii : dom(usuarios) & nn : NOMEUSUARIO
    THEN usuarios := usuarios <+ {ii |-> nn}
    END;

addCredit(ii, cc) =
    PRE ii: IDUSUARIO & cc : NAT1 & ii : dom(creditousuario) & (creditousuario(ii) + cc) : NAT
    THEN creditousuario(ii) := creditousuario(ii) + cc
    END;
    
withdrawCredit(ii, cc) = 
    PRE ii: IDUSUARIO & cc : NAT1 &
	ii : dom(creditousuario) &
	((creditousuario(ii) - cc) : NAT) &
	cc <= creditousuario(ii) &
	ii /: dom(dividausuario)
    THEN creditousuario := creditousuario <+ {ii |-> creditousuario(ii) - cc}
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
    PRE ii : IDPRODUTO & ii : dom(produtos) & pp : NAT
    THEN precoproduto := precoproduto <+ {ii |-> pp}
    END;

addProductToCart(uu, pp, qq) =
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
      IF uu /: dom(cartcontents) THEN
          cartcontents(uu) := {pp |-> {precoproduto(pp) |-> qq}}
      ELSE
          IF pp : dom(cartcontents(uu)) THEN
              IF precoproduto(pp) : dom(cartcontents(uu)(pp)) THEN
                  cartcontents(uu)(pp)(precoproduto(pp)) := cartcontents(uu)(pp)(precoproduto(pp)) + qq
              ELSE
                  cartcontents(uu)(pp) := cartcontents(uu)(pp) \/ {precoproduto(pp) |-> qq}
              END
          ELSE
              cartcontents(uu) := cartcontents(uu) \/ {pp |-> {precoproduto(pp) |-> qq}}
          END
      END ||
      creditousuario := creditousuario <+ {
          uu |-> (creditousuario(uu) - (precoproduto(pp) * qq)),
          dono~(pp) |-> (creditousuario(dono~(pp)) + (precoproduto(pp) * qq))
      } ||
      estoque(pp) := estoque(pp) - qq
    END;


removeProductFromCart(uu, pp, rr, qq) =
  PRE
    uu : IDUSUARIO &
    uu : dom(cartcontents) &
    pp : dom(cartcontents(uu)) &
    rr : NAT &
    qq : NAT1 &
    rr : dom(cartcontents(uu)(pp)) &
    qq <= cartcontents(uu)(pp)(rr)
  THEN
    IF dono~(pp) : dom(dividausuario) THEN
        dividausuario(dono~(pp)) := dividausuario(dono~(pp)) + (cartcontents(uu)(pp)(rr) * rr)
    ELSE
        dividausuario := dividausuario \/ {dono~(pp) |-> cartcontents(uu)(pp)(rr) * rr}
    END ||
    creditousuario(uu) := creditousuario(uu) + cartcontents(uu)(pp)(rr) * rr ||
    IF qq = cartcontents(uu)(pp)(rr) THEN
      IF card(cartcontents(uu)(pp)) <= 1 THEN
           cartcontents(uu) := {pp} <<| cartcontents(uu)
      ELSE
          cartcontents(uu)(pp) := {rr} <<| cartcontents(uu)(pp)
      END
    ELSE
      cartcontents(uu)(pp)(rr) := cartcontents(uu)(pp)(rr) - qq
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
    PRE uu : IDUSUARIO & uu : dom(usuariosinativos)
    THEN 
        usuariosinativos := usuariosinativos <+ {uu |-> 0}
    END;
    
removeInactiveUser(uu) =
    PRE uu : IDUSUARIO & uu : dom(usuariosinativos) & usuariosinativos(uu) <= 0
    THEN 
        usuariosinativos := {uu} <<| usuariosinativos
    END
END