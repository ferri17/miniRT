/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx_ui.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 01:50:49 by fbosch            #+#    #+#             */
/*   Updated: 2023/12/19 02:25:58 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINILIBX_UI_H
# define MINILIBX_UI_H

# include <stdint.h>
# include <stdbool.h>

# define SLIDER_PX 5
# define SLIDER_HEIGHT 30

typedef struct s_slider
{
	uint16_t	length;
	int			min_value;
	int			max_value;
	int			*value;
	int			pos_x;
	int			pos_y;
	bool		is_clicked;
}	t_slider;

#endif
