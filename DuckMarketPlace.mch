MACHINE
    DuckMarketPlace

SETS
    NOMEPRODUTO; NOMEUSUARIO; IDUSUARIO; IDPRODUTO; QUANTIDADEPRODUTO; PRECO
    
VARIABLES
    usuarios, creditousuario, produtos, carrinho, estoque, precoproduto, dono
    
INVARIANT
    usuarios : IDUSUARIO >+> NOMEUSUARIO & // Há IDs unicos para cada usuario mesmo com nomes repetidos
    creditousuario : IDUSUARIO >+> NAT & // Um usuario pode ter no máximo um valode de crédito
    produtos: IDPRODUTO >+> NOMEPRODUTO & // Há IDs unicos para cada produto mesmo com nomes repetidos
    carrinho : IDUSUARIO <-> IDPRODUTO & // Um usuario pode ter varios produtos no carrinho e um produto pode está em varios carrinhos
    estoque : IDPRODUTO >+> QUANTIDADEPRODUTO & // Um produto tem no máximo um valor de estoque, e pode ser iniciaçizado sem ter
    precoproduto : IDPRODUTO >+> PRECO & // Um produto tem no máximo um preço, e pode ser iniciaçizado sem ter
    dono : IDUSUARIO +->> IDPRODUTO // Todo produto tem um dono

INITIALISATION
    usuarios := {} || creditousuario := {} || produtos := {} || carrinho := {} || estoque := {} || precoproduto := {} || dono := {}

OPERATIONS

adduser(ii, nn, cc) =
    PRE ii : IDUSUARIO & nn : NOMEUSUARIO & cc : NAT &
        (ii /: dom(usuarios) & ii /: dom(creditousuario)) & usuarios[{ii}] : {}
    THEN usuarios := usuarios \/ {ii |-> nn} ||
         creditousuario := creditousuario \/ {ii |-> cc}
    END;
    
removeuser(ii) =
    PRE ii : IDUSUARIO & ii : dom(usuarios) & ii : dom(creditousuario)
    THEN usuarios := {ii} <<| usuarios ||
         creditousuario := {ii} <<| creditousuario //Ainda tem que remover carrinho
    END;

altnomeusuario(ii, nn) =
    PRE ii : IDUSUARIO & ii : dom(usuarios) & nn : NOMEUSUARIO
    THEN usuarios := usuarios <+ {ii |-> nn}
    END;

addcredito(ii, cc) =
    PRE ii: IDUSUARIO & cc : NAT & ii : dom(creditousuario) & ((creditousuario(ii) + cc) : NAT)
    THEN creditousuario := creditousuario <+ {ii |-> creditousuario(ii) + cc}
    END;
    
sacarcredito(ii, cc) = 
    PRE ii: IDUSUARIO & cc : NAT & ii : dom(creditousuario) & ((creditousuario(ii) - cc) : NAT) & cc <= creditousuario(ii)
    THEN creditousuario := creditousuario <+ {ii |-> creditousuario(ii) - cc}
    END

END