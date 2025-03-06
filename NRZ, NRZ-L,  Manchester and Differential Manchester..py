import numpy as np
import matplotlib.pyplot as plt

def nrz(bits, sampling_rate, bit_rate):
    bit_duration = 1 / bit_rate
    samples_per_bit = int(sampling_rate / bit_rate)
    t = np.linspace(0, len(bits) * bit_duration, len(bits) * samples_per_bit, endpoint=False)
    signal = np.zeros(len(bits) * samples_per_bit)
    for i, bit in enumerate(bits):
        signal[i * samples_per_bit: (i + 1) * samples_per_bit] = 1 if bit == '1' else -1
    return t, signal

def nrz_l(bits, sampling_rate, bit_rate):
    return nrz(bits, sampling_rate, bit_rate)

def manchester(bits, sampling_rate, bit_rate):
    bit_duration = 1 / bit_rate
    samples_per_bit = int(sampling_rate / bit_rate)
    t = np.linspace(0, len(bits) * bit_duration, len(bits) * samples_per_bit, endpoint=False)
    signal = np.zeros(len(bits) * samples_per_bit)
    for i, bit in enumerate(bits):
        half_samples = samples_per_bit // 2
        if bit == '1':
            signal[i * samples_per_bit: i * samples_per_bit + half_samples] = 1
            signal[i * samples_per_bit + half_samples: (i + 1) * samples_per_bit] = -1
        else:
            signal[i * samples_per_bit: i * samples_per_bit + half_samples] = -1
            signal[i * samples_per_bit + half_samples: (i + 1) * samples_per_bit] = 1
    return t, signal

def differential_manchester(bits, sampling_rate, bit_rate):
    bit_duration = 1 / bit_rate
    samples_per_bit = int(sampling_rate / bit_rate)
    t = np.linspace(0, len(bits) * bit_duration, len(bits) * samples_per_bit, endpoint=False)
    signal = np.zeros(len(bits) * samples_per_bit)
    prev_level = 1
    for i, bit in enumerate(bits):
        half_samples = samples_per_bit // 2
        if bit == '1':
            signal[i * samples_per_bit: i * samples_per_bit + half_samples] = -prev_level
            signal[i * samples_per_bit + half_samples: (i + 1) * samples_per_bit] = prev_level
        else:
            signal[i * samples_per_bit: i * samples_per_bit + half_samples] = prev_level
            signal[i * samples_per_bit + half_samples: (i + 1) * samples_per_bit] = -prev_level
        prev_level = signal[i * samples_per_bit + half_samples]
    return t, signal

# Define parameters
bit_rate = 2
sampling_rate = 1000
duration = 4

# Generate a random binary sequence
np.random.seed(0)
bits = ''.join(np.random.choice(['0', '1'], int(bit_rate * duration)))

# Encode signals using different methods
t_nrz, nrz_signal = nrz(bits, sampling_rate, bit_rate)
t_nrz_l, nrz_l_signal = nrz_l(bits, sampling_rate, bit_rate)
t_manchester, manchester_signal = manchester(bits, sampling_rate, bit_rate)
t_diff_manchester, diff_manchester_signal = differential_manchester(bits, sampling_rate, bit_rate)

# Plot the original binary sequence and the encoded signals
fig, axs = plt.subplots(5, 1, figsize=(8, 8))

# Plot the binary sequence
axs[0].step(np.arange(len(bits)), [int(bit) for bit in bits], where='mid', label='Original Binary Sequence')
axs[0].set_title('Original Binary Sequence', fontsize=14, fontweight='bold', color='blue')
axs[0].set_ylim(-0.5, 1.5)
axs[0].set_xlabel('Bit Index')
axs[0].set_ylabel('Amplitude')
axs[0].grid(True)
axs[0].legend()

# Plot the NRZ signal
axs[1].plot(t_nrz, nrz_signal, label='NRZ Signal')
axs[1].set_title('NRZ Signal', fontsize=14, fontweight='bold', color='blue')
axs[1].set_xlabel('Time [s]')
axs[1].set_ylabel('Amplitude')
axs[1].grid(True)
axs[1].legend()

# Plot the NRZ-L signal
axs[2].plot(t_nrz_l, nrz_l_signal, label='NRZ-L Signal')
axs[2].set_title('NRZ-L Signal', fontsize=14, fontweight='bold', color='blue')
axs[2].set_xlabel('Time [s]')
axs[2].set_ylabel('Amplitude')
axs[2].grid(True)
axs[2].legend()

# Plot the Manchester signal
axs[3].plot(t_manchester, manchester_signal, label='Manchester Signal')
axs[3].set_title('Manchester Signal', fontsize=14, fontweight='bold', color='blue')
axs[3].set_xlabel('Time [s]')
axs[3].set_ylabel('Amplitude')
axs[3].grid(True)
axs[3].legend()

# Plot the Differential Manchester signal
axs[4].plot(t_diff_manchester, diff_manchester_signal, label='Differential Manchester Signal')
axs[4].set_title('Differential Manchester Signal', fontsize=14, fontweight='bold', color='blue')
axs[4].set_xlabel('Time [s]')
axs[4].set_ylabel('Amplitude')
axs[4].grid(True)
axs[4].legend()

# Adjust spacing between subplots
plt.tight_layout()
plt.subplots_adjust(hspace=1.5)
plt.show()

# Print the binary sequence
print("Original Binary Sequence:")
print(bits)
