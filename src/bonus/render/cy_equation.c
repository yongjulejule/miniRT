x = (+ & -sqrt((-4 a d g^2 + 2 a d - 4 a e g h - 4 a f g j - 4 b d g h - 4 b e h^2 + 2 b e - 4 b f h j - 4 c d g j - 4 c e h j - 4 c f j^2 + 2 c f)^2 - 4 (-2 d^2 g^2 + d^2 - 4 d e g h - 4 d f g j - 2 e^2 h^2 + e^2 - 4 e f h j - 2 f^2 j^2 + f^2) (-2 a^2 g^2 + a^2 - 4 a b g h - 4 a c g j - 2 b^2 h^2 + b^2 - 4 b c h j - 2 c^2 j^2 + c^2 - r^2)) 
+ 4 a d g^2 - 2 a d + 4 a e g h + 4 a f g j + 4 b d g h + 4 b e h^2 - 2 b e + 4 b f h j + 4 c d g j + 4 c e h j + 4 c f j^2 - 2 c f)
/ (2 (-2 d^2 g^2 + d^2 - 4 d e g h - 4 d f g j - 2 e^2 h^2 + e^2 - 4 e f h j - 2 f^2 j^2 + f^2))


a = ((-2 d^2 g^2 + d^2 - 4 d e g h - 4 d f g j - 2 e^2 h^2 + e^2 - 4 e f h j - 2 f^2 j^2 + f^2))
b = (-4 a d g^2 + 2 a d - 4 a e g h - 4 a f g j - 4 b d g h - 4 b e h^2 + 2 b e - 4 b f h j - 4 c d g j - 4 c e h j - 4 c f j^2 + 2 c f)
c = (-2 a^2 g^2 + a^2 - 4 a b g h - 4 a c g j - 2 b^2 h^2 + b^2 - 4 b c h j - 2 c^2 j^2 + c^2 - r^2)

d^2 + e^2 + f^2 = 1
g^2 + h^2 + j^2 = 1

a = ((-2 d^2 g^2 - 4 d e g h - 4 d f g j - 2 e^2 h^2 - 4 e f h j - 2 f^2 j^2 + 1))
b = (-4 a d g^2 + 2 a d - 4 a e g h - 4 a f g j - 4 b d g h - 4 b e h^2 + 2 b e - 4 b f h j - 4 c d g j - 4 c e h j - 4 c f j^2 + 2 c f)
c = (-2 a^2 g^2 + a^2 - 4 a b g h - 4 a c g j - 2 b^2 h^2 + b^2 - 4 b c h j - 2 c^2 j^2 + c^2 - r^2)

a = ((-2 r[X]^2 hy->o_vect[X]^2 - 4 r[X] r[Y] hy->o_vect[X] hy->o_vect[Y]
- 4 r[X] r[Z] hy->o_vect[X] hy->o_vect[Z]
- 2 r[Y]^2 hy->o_vect[Y]^2 - 4 r[Y] r[Z] hy->o_vect[Y] hy->o_vect[Z] - 2 r[Z]^2 hy->o_vect[Z]^2 + 1))

b = (-4 diff[X] r[X] hy->o_vect[X]^2 + 2 diff[X] r[X] - 4 diff[X] r[Y] hy->o_vect[X] hy->o_vect[Y] - 4 diff[X] r[Z] hy->o_vect[X] hy->o_vect[Z]
- 4 diff[Y] r[X] hy->o_vect[X] hy->o_vect[Y] - 4 diff[Y] r[Y] hy->o_vect[Y]^2 + 2 diff[Y] r[Y]
- 4 diff[Y] r[Z] hy->o_vect[Y] hy->o_vect[Z] - 4 diff[Z] r[X] hy->o_vect[X] hy->o_vect[Z] - 4 diff[Z] r[Y] hy->o_vect[Y] hy->o_vect[Z] - 4 diff[Z] r[Z] hy->o_vect[Z]^2 + 2 diff[Z] r[Z])

c = (-2 diff[X]^2 hy->o_vect[X]^2 + diff[X]^2 - 4 diff[X] diff[Y] hy->o_vect[X] hy->o_vect[Y]
- 4 diff[X] diff[Z] hy->o_vect[X] hy->o_vect[Z] - 2 diff[Y]^2 hy->o_vect[Y]^2 + diff[Y]^2 - 4 diff[Y] diff[Z] hy->o_vect[Y] hy->o_vect[Z]
- 2 diff[Z]^2 hy->o_vect[Z]^2 + diff[Z]^2 - rad^2) 

/*
a = ((-2 d^2 g^2 - 4 d e g h - 4 d f g j
- 2 e^2 h^2 - 4 e f h j - 2 f^2 j^2 + 1))

b = (-4 a d g^2 + 2 a d - 4 a e g h - 4 a f g j - 4 b d g h - 4 b e h^2 + 2 b e
- 4 b f h j - 4 c d g j - 4 c e h j - 4 c f j^2 + 2 c f)

c = (-2 a^2 g^2 + a^2 - 4 a b g h - 4 a c g j - 2 b^2 h^2 + b^2 - 4 b c h j
- 2 c^2 j^2 + c^2 - r^2) 

where	a, b, c = o - hy->center
		d, e, f = r
		g, h, j = hy->o_vect
*/