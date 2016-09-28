/*
 * Copyright (C) Wilco Vlenterie (wv-tud)
 *
 * This file is part of paparazzi
 *
 * paparazzi is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * paparazzi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with paparazzi; see the file COPYING.  If not, see
 * <http://www.gnu.org/licenses/>.
 */
/**
 * @file "modules/computer_vision//cv_active_random_filter.c"
 * @author Wilco Vlenterie (wv-tud)
 * Active random sampling colour filter
 */

typedef struct _trackResults {
    int     x_p;
    int     y_p;
    double  area_p;
    double 	x_c;
    double 	y_c;
    double 	r_c;
    double  x_b;
    double  y_b;
    double  z_b;
    double  x_w;
    double  y_w;
    double  z_w;
} trackResults;

extern int 		AR_FILTER_GREY_THRESHOLD;
extern int 		AR_FILTER_IMAGE_CROP_FOVY;
extern int 		AR_FILTER_RND_PIX_SAMPLE;
extern int 		AR_FILTER_Y_MIN;
extern int 		AR_FILTER_Y_MAX;
extern int 		AR_FILTER_CB_MIN;
extern int 		AR_FILTER_CB_MAX;
extern int 		AR_FILTER_CR_MIN;
extern int 		AR_FILTER_CR_MAX;
extern int		AR_FILTER_SAMPLE_STYLE;
extern int 		AR_FILTER_FLOOD_STYLE;

// Filter sample styles
#define AR_FILTER_STYLE_FULL   0
#define AR_FILTER_STYLE_GRID   1
#define AR_FILTER_STYLE_RANDOM 2
// Filter flood styles
#define AR_FILTER_FLOOD_OMNI   0
#define AR_FILTER_FLOOD_CW     1

#ifdef __cplusplus
extern "C" {
#endif

void active_random_filter(char* buff, int width, int height);

#ifdef __cplusplus
}
#endif
