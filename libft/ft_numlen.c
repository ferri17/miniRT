/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 11:37:23 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/15 11:45:56 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_numlen(int n)
{
	int	qtt10;
	int	ext;
	int	len;

	ext = 0;
	len = 0;
	qtt10 = 1;
	while (qtt10 <= n && ext == 0)
	{
		if (qtt10 < 1000000000)
		{
			qtt10 *= 10;
			len++;
		}
		else
		{
			ext = 1;
			len++;
		}
	}
	if (n == 0)
		len = 1;
	return (len);
}
