import cv2
import numpy as np

H, W = map(int, input().split())
tmp = ""
for _ in range(H):
    tmp += input().strip() + "\n"


def generate_image(rows, cols, pattern):
    lines = pattern.strip().split("\n")
    image = np.zeros((rows, cols, 3), dtype=np.uint8)

    for i in range(rows):
        for j in range(cols):
            if lines[i][j] == ".":
                image[i, j] = [255, 255, 255]
            elif lines[i][j] == "#":
                image[i, j] = [0, 0, 0]
    return image


image = generate_image(H, W, tmp)

# 画像をグレースケールに変換してから二値化
gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
_, threshold = cv2.threshold(gray_image, 127, 255, cv2.THRESH_BINARY)

# 輪郭を検出
contours, _ = cv2.findContours(threshold, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

# 近似多角形を計算
for contour in contours:
    epsilon = 0.01 * cv2.arcLength(contour, True)
    approx = cv2.approxPolyDP(contour, epsilon, True)
    print(len(approx))
    break
