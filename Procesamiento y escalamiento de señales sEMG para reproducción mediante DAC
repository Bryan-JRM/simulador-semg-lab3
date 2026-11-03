!pip install wfdb

import wfdb
import numpy as np
import matplotlib.pyplot as plt

carpeta = "grabmyo/1.1.0/Session1/session1_participant1"

gestos = {
    "Reposo": 17,
    "Cierre de mano": 16,
    "Extensión del índice": 9
}

canal = 11   # F12 corresponde al índice 11 en Python

senales = {}

for nombre_g, k in gestos.items():
    rec = wfdb.rdrecord(
        f"session1_participant1_gesture{k}_trial1",
        pn_dir=carpeta
    )
    senales[nombre_g] = rec.p_signal[:, canal]

fig, ax = plt.subplots(3, 1, sharex=True, sharey=True)

for a, (nombre_g, x) in zip(ax, senales.items()):
    a.plot(np.arange(len(x)) / rec.fs, x)
    a.set_title(nombre_g)
    a.set_ylabel("mV")

ax[-1].set_xlabel("Tiempo (s)")
plt.show()

# Concatenacion de las señales
secuencia = np.concatenate([
    senales["Reposo"],
    senales["Cierre de mano"],
    senales["Extensión del índice"]
])

print("Número de muestras:", len(secuencia))

# Escalamiento lineal de toda la secuencia
minimo = np.min(secuencia)
maximo = np.max(secuencia)

secuencia_8bits = (secuencia - minimo) / (maximo - minimo) * 255
secuencia_8bits = secuencia_8bits.astype(np.uint8)

print("Valor mínimo:", secuencia_8bits.min())
print("Valor máximo:", secuencia_8bits.max())

tiempo = np.arange(len(secuencia_8bits)) / 2048

plt.figure(figsize=(12,4))
plt.plot(tiempo, secuencia_8bits)

plt.xlabel("Tiempo (s)")
plt.ylabel("Valor DAC")
plt.title("Secuencia sEMG escalada a 8 bits")
plt.grid()

plt.show()

with open("semg.h", "w") as f:
    f.write("#include <stdint.h>\n\n")
    f.write("const uint8_t SEMG[] = {\n")

    for i, valor in enumerate(secuencia_8bits):
        f.write(str(valor))
        if i < len(secuencia_8bits) - 1:
            f.write(", ")

        if (i + 1) % 20 == 0:
            f.write("\n")

    f.write("\n};\n\n")
    f.write(f"const unsigned int N_SEMG = {len(secuencia_8bits)};\n")
    f.write("const unsigned int FS_SEMG = 2048;\n")

print("semg.h creado")
