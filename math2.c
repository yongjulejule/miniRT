first = pow(vect_size(r), 2) - 2 * (a * b * g * h + a * c * g * i + b * c * h * i) - pow(a * g, 2) - pow(b * h, 2) - pow(c * i, 2)

second = 2 * (a * d * pow(g, 2) - a * d + a * e * g * h + a * f * g * i - a * pow(g, 2) * j - a * g * h * k - a * g * i * l + a * j + b * d * g * h + b * e * pow(h, 2) - b * e + b * f * h * i - b * g * h * j - b * pow(h, 2) * k - b * h * i * l + b * k + c * d * g * i + c * e * h * i + c * f * pow(i, 2) - c * f - c * g * i * j - c * h * i * k - c * pow(i, 2) * l + c * l)

third = pow(vect_size(cy->center), 2) + pow(vect_size(o), 2) + 2 * (d * pow(g, 2) * j - d * e * g * h - d * f * g * i + d * g * h * k + d * g * i * l - d * j - e * f * h * i + e * g * h * j + e * pow(h, 2) * k + e * h * i * l - e * k + f * g * i * j + f * h * i * k + f *pow(i, 2) * l - f * l - g * h * j * k - g * i * j * l - h * i * k * l) - pow(e * h, 2) - pow(f * i, 2) - pow(g * j, 2) - pow(h * k, 2) - pow(i * l, 2) - pow(rad, 2) - pow(d * g, 2)
