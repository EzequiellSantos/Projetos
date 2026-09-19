import numpy as np
import matplotlib.pyplot as plt
import scipy.io.wavfile as wav
from scipy.fftpack import fft, fftshift

# Carregar o arquivo de áudio fornecido
audio_path = "audioA.wav"
fs, audio = wav.read(audio_path)  # Ler o arquivo de áudio

# Verificar dimensões do áudio (estéreo ou mono)
if len(audio.shape) > 1:  # Áudio estéreo
    sinal = audio[:, 0]  # Usar apenas o primeiro canal
else:  # Áudio mono
    sinal = audio

# Criar vetor de tempo
t = np.arange(len(sinal)) / fs

# 1) Plotar o sinal no domínio do tempo
plt.figure(figsize=(10, 4))
plt.plot(t, sinal)
plt.title("Sinal de Áudio no Tempo")
plt.xlabel("Tempo (s)")
plt.ylabel("Amplitude")
plt.grid()
plt.show()

# 2) Transformada de Fourier
N = len(sinal)
freqs = np.linspace(-fs/2, fs/2, N)
sinal_fft = fftshift(fft(sinal))

plt.figure(figsize=(10, 4))
plt.plot(freqs, np.abs(sinal_fft))
plt.title("Transformada de Fourier do Sinal")
plt.xlabel("Frequência (Hz)")
plt.ylabel("Magnitude")
plt.grid()
plt.show()

# 3) Modulação para faixa entre 0.6π e 0.8π rad
w0 = 0.7 * np.pi * fs  # Frequência central da modulação
sinal_modulado = sinal * np.cos(2 * np.pi * w0 * t)

plt.figure(figsize=(10, 4))
plt.plot(t, sinal_modulado)
plt.title("Sinal Modulado no Tempo")
plt.xlabel("Tempo (s)")
plt.ylabel("Amplitude")
plt.grid()
plt.show()

# 4) Transformada de Fourier do sinal modulado
sinal_mod_fft = fftshift(fft(sinal_modulado))

plt.figure(figsize=(10, 4))
plt.plot(freqs, np.abs(sinal_mod_fft))
plt.title("Transformada de Fourier do Sinal Modulado")
plt.xlabel("Frequência (Hz)")
plt.ylabel("Magnitude")
plt.grid()
plt.show()

# 5) Adicionar ruído branco gaussiano
ruido = np.sqrt(0.05) * np.random.randn(N)
sinal_ruidoso = sinal + ruido

plt.figure(figsize=(10, 4))
plt.plot(t, sinal_ruidoso)
plt.title("Sinal Ruidoso no Tempo")
plt.xlabel("Tempo (s)")
plt.ylabel("Amplitude")
plt.grid()
plt.show()

# 6) Transformada de Fourier do sinal ruidoso
sinal_ruidoso_fft = fftshift(fft(sinal_ruidoso))

plt.figure(figsize=(10, 4))
plt.plot(freqs, np.abs(sinal_ruidoso_fft))
plt.title("Transformada de Fourier do Sinal Ruidoso")
plt.xlabel("Frequência (Hz)")
plt.ylabel("Magnitude")
plt.grid()
plt.show()
