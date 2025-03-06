import numpy as np
import matplotlib.pyplot as plt

def ask(bits, sampling_rate, bit_rate, carrier_frequency):
    bit_duration = 1 / bit_rate
    samples_per_bit = int(sampling_rate / bit_rate)
    t = np.linspace(0, len(bits) * bit_duration, len(bits) * samples_per_bit, endpoint=False)
    signal = np.zeros(len(bits) * samples_per_bit)
    for i, bit in enumerate(bits):
        if bit == '1':
            signal[i * samples_per_bit: (i + 1) * samples_per_bit] = np.sin(2 * np.pi * carrier_frequency * t[i * samples_per_bit: (i + 1) * samples_per_bit])
    return t, signal

def fsk(bits, sampling_rate, bit_rate, carrier_frequency, deviation):
    bit_duration = 1 / bit_rate
    samples_per_bit = int(sampling_rate / bit_rate)
    t = np.linspace(0, len(bits) * bit_duration, len(bits) * samples_per_bit, endpoint=False)
    signal = np.zeros(len(bits) * samples_per_bit)
    for i, bit in enumerate(bits):
        if bit == '1':
            signal[i * samples_per_bit: (i + 1) * samples_per_bit] = np.sin(2 * np.pi * (carrier_frequency + deviation) * t[i * samples_per_bit: (i + 1) * samples_per_bit])
        else:
            signal[i * samples_per_bit: (i + 1) * samples_per_bit] = np.sin(2 * np.pi * (carrier_frequency - deviation) * t[i * samples_per_bit: (i + 1) * samples_per_bit])
    return t, signal

def psk(bits, sampling_rate, bit_rate, carrier_frequency):
    bit_duration = 1 / bit_rate
    samples_per_bit = int(sampling_rate / bit_rate)
    t = np.linspace(0, len(bits) * bit_duration, len(bits) * samples_per_bit, endpoint=False)
    signal = np.zeros(len(bits) * samples_per_bit)
    for i, bit in enumerate(bits):
        phase = 0 if bit == '0' else np.pi
        signal[i * samples_per_bit: (i + 1) * samples_per_bit] = np.sin(2 * np.pi * carrier_frequency * t[i * samples_per_bit: (i + 1) * samples_per_bit] + phase)
    return t, signal

# Define parameters
bit_rate = 2
sampling_rate = 1000
duration = 2
carrier_frequency = 5
deviation = 5

# Generate a random binary sequence
np.random.seed(0)
bits = ''.join(np.random.choice(['0', '1'], int(bit_rate * duration)))

# Modulate signals using different techniques
t_ask, ask_signal = ask(bits, sampling_rate, bit_rate, carrier_frequency)
t_fsk, fsk_signal = fsk(bits, sampling_rate, bit_rate, carrier_frequency, deviation)
t_psk, psk_signal = psk(bits, sampling_rate, bit_rate, carrier_frequency)

# Plot the original binary sequence and the modulated signals
plt.figure(figsize=(15, 8))

# Plot the binary sequence
plt.step(np.arange(len(bits)), [int(bit) for bit in bits], where='mid', label='Original Binary Sequence')

# Plot the ASK signal
plt.plot(t_ask, ask_signal, label='ASK Signal')

# Plot the FSK signal
plt.plot(t_fsk, fsk_signal, label='FSK Signal')

# Plot the PSK signal
plt.plot(t_psk, psk_signal, label='PSK Signal')

plt.title('Digital-Analog Conversion Techniques', fontsize=16, fontweight='bold', color='blue')
plt.xlabel('Time [s]', fontsize=12)
plt.ylabel('Amplitude', fontsize=12)
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()
