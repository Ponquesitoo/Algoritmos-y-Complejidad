import matplotlib.pyplot as plt

# hacer una funcion que permita procesar dos archivos y convertirlos en arreglos.
def leer_archivo(nombreArchivo):
    numeros = []
    with open(nombreArchivo, 'r') as archivo:
        for linea in archivo:
            try:
                numeros.append(float(linea.strip()))
            except ValueError:
                print(f"linea no valida ignorada")
    return numeros

# algoritmo de fuerza bruta
FBarchivo_x = "textos/FB/tiempos_transposiciones.txt"
FBarchivo_y = "textos/FB/tamanio_transposiciones.txt"

FB_x = leer_archivo(FBarchivo_x)
FB_y = leer_archivo(FBarchivo_y)

# algoritmo de programacion dinamica
PDarchivo_x = "textos/PD/tiempos_transposiciones_PD.txt"
PDarchivo_y = "textos/PD/tamanio_transposiciones_PD.txt"

PD_x = leer_archivo(PDarchivo_x)
PD_y = leer_archivo(PDarchivo_y)

plt.plot(FB_x, FB_y, marker='o', color='blue', label="Fuerza Bruta", linestyle='-')
plt.plot(PD_x, PD_y, marker='o', color='red', label="Programacion Dinamica", linestyle='-')

# plt.scatter(FB_x, FB_y, color='blue', s=50, label="Fuerza Bruta")
# plt.scatter(PD_x, PD_y, color='red', s=50, label="Programacion Dinamica")

plt.xlabel("tiempo")
plt.ylabel("pares de cadenas")
plt.legend()
plt.grid(True)

plt.xticks(range(0, int(max(FB_x + PD_x)) + 1, 100))
# plt.yticks(range(0, int(max(FB_y + PD_y))+1, 20))

plt.show()
