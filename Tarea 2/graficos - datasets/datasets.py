import random
import string

def generar_vacioS1(output_file):
    with open(output_file, "w") as f:
        for _ in range(400):
            s1 = ""  # Cadena vacia
            s2 = "".join(random.choices(string.ascii_lowercase, k=random.randint(1, 10)))
            f.write(f"{s1},{s2}\n")

def generar_vacioS2(output_file):
    with open(output_file, "w") as f:
        for _ in range(400):
            s1 = ""  # Cadena vacia
            s2 = "".join(random.choices(string.ascii_lowercase, k=random.randint(1, 10)))
            f.write(f"{s2},{s1}\n")

def generar_repetidos(output_file):
    with open(output_file, "w") as f:
        for _ in range(400):
            s1 = "a" * random.randint(1, 7)
            s2 = "a" * random.randint(1, 7)
            f.write(f"{s1},{s2}\n")

def generar_transposiciones(output_file):
    with open(output_file, "w") as f:
        for _ in range(400):
            base = "".join(random.choices(string.ascii_lowercase, k=6))
            idx = random.randint(1, len(base) - 2)
            s2 = base[:idx] + base[idx + 1] + base[idx] + base[idx + 2:]
            f.write(f"{base},{s2}\n")

def generar_largo(output_file):
    with open(output_file, "w") as f:
        for _ in range(400):
            s1 = "".join(random.choices(string.ascii_lowercase, k=7))
            s2 = "".join(random.choices(string.ascii_lowercase, k=7))
            f.write(f"{s1},{s2}\n")

def generar_largo_variable(output_file):
    with open(output_file, "w") as f:
        for _ in range(400):
            s1 = "".join(random.choices(string.ascii_lowercase, k=random.randint(2, 8)))
            s2 = "".join(random.choices(string.ascii_lowercase, k=random.randint(3, 9)))
            f.write(f"{s1},{s2}\n")

# Llamadas para generar los archivos
generar_vacioS1("vacioS1.txt")
generar_repetidos("repetidos.txt")
generar_transposiciones("transposiciones.txt")
generar_largo("largo.txt")
generar_largo_variable("largo_variable.txt")
generar_vacioS2("vacioS2.txt")
