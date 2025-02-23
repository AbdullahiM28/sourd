function playSound() {
    const audioContext = new (window.AudioContext || window.webkitAudioContext)();
    const oscillator = audioContext.createOscillator();
    oscillator.type = 'sine';  // Sound type: sine wave
    oscillator.frequency.setValueAtTime(440, audioContext.currentTime); // A4 note (440 Hz)
    oscillator.connect(audioContext.destination);
    oscillator.start();
    oscillator.stop(audioContext.currentTime + 1);  // Stop after 1 second
  }
  