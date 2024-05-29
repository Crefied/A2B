# i n c l u d e   " m a i n w i n d o w . h "  
 # i n c l u d e   " . / u i _ m a i n w i n d o w . h "  
 # i n c l u d e " . / u i _ g a m e w i n d o w . h "  
 # i n c l u d e < Q F i l e >  
 # i n c l u d e < Q D e b u g >  
 # i n c l u d e < Q D i r >  
  
  
 M a i n W i n d o w : : M a i n W i n d o w ( G a m e W i n d o w   *   _ g a m e w i n d o w , Q W i d g e t   * p a r e n t )  
         :   Q M a i n W i n d o w ( p a r e n t )  
         ,   u i ( n e w   U i : : M a i n W i n d o w )  
 {  
         u i - > s e t u p U i ( t h i s ) ;  
  
         Q F i l e I n f o   f i l e I n f o ( _ _ F I L E _ _ ) ;  
         Q D i r   s o u r c e D i r   =   f i l e I n f o . d i r ( ) ;  
         Q S t r i n g   s t y l e S h e e t P a t h   =   s o u r c e D i r . f i l e P a t h ( " s t y l e . q s s " ) ;  
         / / Q T a b W i d g e t *   s t a g e W i d g e t   =   d y n a m i c _ c a s t < Q T a b W i d g e t * > ( u i - > s t a c k e d W i d g e t - > w i d g e t ( 1 ) ) ;  
  
         g a m e w i n d o w   =   _ g a m e w i n d o w ;  
  
         Q F i l e   f i l e ( s t y l e S h e e t P a t h ) ;  
         i f   ( f i l e . o p e n ( Q F i l e : : R e a d O n l y ) )  
         {  
                 s t y l e S h e e t   =   Q L a t i n 1 S t r i n g ( f i l e . r e a d A l l ( ) ) ;  
                 q D e b u g ( )   < <   " S t y l e   s h e e t : "   < <   s t y l e S h e e t ;  
         }  
         e l s e  
         {  
                 q D e b u g ( )   < <   " F a i l e d   t o   o p e n   s t y l e . q s s "   < <   f i l e . e r r o r S t r i n g ( )   < <   Q D i r : : c u r r e n t P a t h ( ) ;  
         }  
  
  
  
         t h i s - > s e t S t y l e S h e e t ( s t y l e S h e e t ) ;  
         / / g a m e w i n d o w - > s e t S t y l e S h e e t ( s t y l e S h e e t ) ;  
  
  
  
         t h i s - > s e t W i n d o w T i t l e ( " A 2 B " ) ;  
         s t a c k e d W i d g e t   =   u i - > c e n t r a l w i d g e t - > f i n d C h i l d < Q S t a c k e d W i d g e t * > ( " s t a c k e d W i d g e t " ) ;  
         s t a c k e d W i d g e t - > s e t C u r r e n t I n d e x ( 0 ) ;  
         u i - > s t a c k e d W i d g e t - > l a y o u t ( ) - > s e t A l i g n m e n t ( Q t : : A l i g n R i g h t ) ;  
         t h i s - > s e t G e o m e t r y ( 0 ,   0 ,   8 0 0 ,   6 0 0 ) ;  
         / / u i - > s t a c k e d W i d g e t - > a d d W i d g e t ( g a m e w i n d o w ) ;  
  
         c o n n e c t ( g a m e w i n d o w - > u i - > b a c k B u t t o n ,   & Q P u s h B u t t o n : : c l i c k e d ,   t h i s ,   [ = ] ( )  
                 {  
                         g a m e w i n d o w - > h i d e ( ) ;  
                         t h i s - > s h o w ( ) ;  
                         u i - > s t a c k e d W i d g e t - > s e t C u r r e n t I n d e x ( 0 ) ;  
                 } ) ;  
  
         c o n n e c t ( u i - > s t a r t P u s h B u t t o n ,   & Q P u s h B u t t o n : : c l i c k e d ,   t h i s ,   [ = ] ( ) {  
                 u i - > s t a c k e d W i d g e t - > s e t C u r r e n t I n d e x ( 1 ) ;  
                 } ) ;  
  
         c o n n e c t ( u i - > b a c k P u s h B u t t o n ,   & Q P u s h B u t t o n : : c l i c k e d ,   t h i s ,   [ = ] ( )  
                 {  
                         u i - > s t a c k e d W i d g e t - > s e t C u r r e n t I n d e x ( 0 ) ;  
                 } ) ;  
         c o n n e c t ( u i - > o p t i o n P u s h B u t t o n ,   & Q P u s h B u t t o n : : c l i c k e d ,   t h i s ,   [ = ] ( )  
                 {  
                         u i - > s t a c k e d W i d g e t - > s e t C u r r e n t I n d e x ( 2 ) ;  
                 } ) ;  
  
         Q T a b W i d g e t *   t a b W i d g e t   =   u i - > t a b W i d g e t ;  
         f o r   ( i n t   i   =   0 ;   i   <   t a b W i d g e t - > c o u n t ( ) ;   + + i )  
         {  
                 Q W i d g e t *   t a b   =   t a b W i d g e t - > w i d g e t ( i ) ;  
                 Q L i s t < Q P u s h B u t t o n * >   b u t t o n s   =   t a b - > f i n d C h i l d r e n < Q P u s h B u t t o n * > ( ) ;  
                 f o r   ( Q P u s h B u t t o n *   b u t t o n   :   b u t t o n s )  
                 {  
                         c o n n e c t ( b u t t o n ,   & Q P u s h B u t t o n : : c l i c k e d ,   t h i s ,   [ = ] ( )  
                                 {  
                                         t h i s - > h i d e ( ) ;  
                                         t h i s - > g a m e w i n d o w - > s h o w ( ) ;  
                                 } ) ;  
                 }  
         }  
  
  
  
  
 }  
  
  
  
 M a i n W i n d o w : : ~ M a i n W i n d o w ( )  
 {  
         u i - > s t a c k e d W i d g e t - > r e m o v e W i d g e t ( g a m e w i n d o w ) ;  
         / / d e l e t e   u i ;  
 }  
  
 v o i d   M a i n W i n d o w : : o n _ p u s h B u t t o n _ c l i c k e d ( )  
 {  
         t h i s - > h i d e ( ) ;  
         t h i s - > g a m e w i n d o w - > s h o w ( ) ;  
 }  
  
  
 