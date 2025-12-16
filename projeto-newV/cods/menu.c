#include <ncurses.h>
#include <string.h>
#include <stdbool.h>
#include "../includes/menu.h"

int select_emoji(const char **emoji, const char **names, int total, int player_id)
{
    int index = 0;
    int prev_index = -1;
    bool first = true;

    nodelay(stdscr, FALSE);

    while (1) {

        if (first || index != prev_index) {
            clear();

            int mid_y = LINES / 2;
            int mid_x = COLS / 2;

            int name_len = (int)strlen(names[index]);
            mvprintw(mid_y - 2, mid_x - name_len/2, "%s", names[index]);

            mvprintw(mid_y, mid_x - 1, "%s", emoji[index]);

            if (player_id == 1)
                mvprintw(LINES - 3, (COLS/2) - 12, "Player %d - Use A / D  ENTER", player_id);
            else
                mvprintw(LINES - 3, (COLS/2) - 12, "Player %d - Use <- / -> ENTER", player_id);

            refresh();
            first = false;
            prev_index = index;
        }

        int ch = getch();

        if (player_id == 1) {
            if (ch == 'a' || ch == 'A') index = (index - 1 + total) % total;
            else if (ch == 'd' || ch == 'D') index = (index + 1) % total;
        } else {
            if (ch == KEY_LEFT) index = (index - 1 + total) % total;
            else if (ch == KEY_RIGHT) index = (index + 1) % total;
        }

        if (ch == '\n' || ch == KEY_ENTER)
            break;
    }

    nodelay(stdscr, TRUE);
    return index;
}
