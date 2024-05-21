from cs50 import get_int


def main():
    height = get_valid_height()
    draw_bricks(height)


def get_valid_height():
    while True:
        height = get_int("Height: ")
        if height > 0 and height < 9:
            break
    return height


def draw_bricks(height):
    for i in range(1, height + 1):
        right_bricks = ("#" * i).rjust(height)
        left_bricks = ("#" * i)
        print(right_bricks + "  " + left_bricks)


main()
