float val;
float s = 0.02;

void draw() {
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width/2; x++) {
      noiseDetail(3,0.4);
      val = noise((mouseX + x) * s, (mouseY + y) * s);
      stroke(val * 255);
      point(x, y);
      noiseDetail(5, 0.6);
      val = noise((mouseX + x + width/2) * s, (mouseY + y) * s);
      stroke(val * 255);
      point(x + width/2, y);
    }
  }
}
