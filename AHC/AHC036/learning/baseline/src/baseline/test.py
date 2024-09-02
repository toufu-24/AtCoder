import pygame
import sys

# Pygameの初期化
pygame.init()

# 画面サイズの設定
width, height = 800, 600
screen = pygame.display.set_mode((width, height))
pygame.display.set_caption("Pygame サンプル")

# 色の設定
red = (255, 0, 0)
black = (0, 0, 0)

# メインループ
while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
    
    # 画面を黒で塗りつぶす
    screen.fill(black)
    
    # 赤い円を描画
    pygame.draw.circle(screen, red, (width // 2, height // 2), 50)
    
    # 画面の更新
    pygame.display.flip()
