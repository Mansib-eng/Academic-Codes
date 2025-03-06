import numpy as np
import matplotlib.pyplot as plt

frequency = 5
duration = 1
sampling_rate = 100

t = np.linspace(0, duration, int(sampling_rate * duration), endpoint=False)
sine_wave = np.sin(2 * np.pi * frequency * t)

pcm_sampling_rate = 50

sampling_interval = int(sampling_rate / pcm_sampling_rate)
sample_indices = np.arange(0, len(t), sampling_interval)
sampled_signal = sine_wave[sample_indices]

num_levels = 16
max_val = np.max(np.abs(sampled_signal))
quantized_signal = np.round((sampled_signal / max_val) * (num_levels / 2))
quantized_signal = np.clip(quantized_signal, -(num_levels / 2), (num_levels / 2) - 1)

def quantized_to_binary(quantized_signal, num_levels):
    num_bits = int(np.ceil(np.log2(num_levels)))
    binary_encoded_signal = [(bin(int(val) & (2**num_bits - 1))[2:]).zfill(num_bits) for val in (quantized_signal + (num_levels // 2)).astype(int)]
    return binary_encoded_signal

binary_encoded_signal = quantized_to_binary(quantized_signal, num_levels)

title_font = {'fontsize': 14, 'fontweight': 'bold', 'color': 'blue'}

plt.figure(figsize=(7.7, 7.7))

# Plot the original sine wave
plt.subplot(4, 1, 1)
plt.plot(t, sine_wave, label="Analog Signal (Sine Wave)")
plt.title("Analog Signal (Sine Wave)", fontdict=title_font)
plt.ylabel("Amplitude")
plt.grid(True)
plt.legend()
plt.xlabel("Time [s]")

# Plot the sampled signal
plt.subplot(4, 1, 2)
plt.plot(t, sine_wave, label="Analog Signal (Sine Wave)", alpha=0.5)
plt.stem(sample_indices / sampling_rate, sampled_signal, basefmt=" ", linefmt="r-", markerfmt="ro", label="Sampled Signal")
plt.title("Sampled Signal", fontdict=title_font)
plt.ylabel("Amplitude")
plt.grid(True)
plt.legend()
plt.xlabel("Time [s]")

# Plot the quantized signal
plt.subplot(4, 1, 3)
plt.plot(t, sine_wave, label="Analog Signal (Sine Wave)", alpha=0.5)
plt.stem(sample_indices / sampling_rate, quantized_signal, basefmt=" ", linefmt="g-", markerfmt="go", label="Quantized Signal")
plt.title("Quantized Signal", fontdict=title_font)
plt.ylabel("Quantized Levels")
plt.grid(True)
plt.legend()
plt.xlabel("Time [s]")

# Display the binary encoded signal
plt.subplot(4, 1, 4)
binary_encoded_str = ' '.join(binary_encoded_signal)
plt.text(0.1, 0.5, binary_encoded_str, fontsize=12, wrap=True)
plt.title("Digital Signal (Binary Encoded)", fontdict=title_font)
plt.axis('off')
#plt.xlabel("Time [s]")

# Adjust spacing between subplots
plt.subplots_adjust(hspace=0.5)

plt.tight_layout()
plt.show()

# Print the binary encoded signal
print("Binary Encoded Signal:")
print(binary_encoded_signal)
