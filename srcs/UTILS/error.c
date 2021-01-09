/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <tvacherat@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 11:45:06 by tvachera          #+#    #+#             */
/*   Updated: 2020/12/22 16:30:01 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	g_ok = true;

bool	report(char *error)
{
	if (g_ok == true)
	{
		write(2, FAIL, ft_strlen(FAIL));
		write(2, "\n", 1);
		g_ok = false;
	}
	if (errno != 0)
	{
		perror(error);
		errno = 0;
	}
	else
	{
		write(2, error, ft_strlen(error));
		write(2, "\n", 1);
	}
	return (false);
}

bool	report2(char *error, char *txt)
{
	if (g_ok == true)
	{
		write(2, FAIL, ft_strlen(FAIL));
		write(2, "\n", 1);
		g_ok = false;
	}
	if (errno != 0)
	{
		perror(error);
		errno = 0;
	}
	else
	{
		write(2, error, ft_strlen(error));
		write(2, ": ", 2);
		write(2, txt, ft_strlen(txt));
		write(2, "\n", 1);
	}
	return (false);
}

bool	report3(char *error, char *to_free, int to_close)
{
	if (g_ok == true)
	{
		write(2, FAIL, ft_strlen(FAIL));
		write(2, "\n", 1);
		g_ok = false;
	}
	if (errno != 0)
	{
		perror(error);
		errno = 0;
	}
	else
	{
		write(2, error, ft_strlen(error));
		write(2, "\n", 1);
	}
	if (to_free)
		free(to_free);
	if (to_close > 0)
		close(to_close);
	return (false);
}

bool	report4(char *error, char *txt, char *to_free, char *to_free2)
{
	if (g_ok == true)
	{
		write(2, FAIL, ft_strlen(FAIL));
		write(2, "\n", 1);
		g_ok = false;
	}
	if (errno != 0)
	{
		perror(error);
		errno = 0;
	}
	else
	{
		write(2, error, ft_strlen(error));
		write(2, ": ", 2);
		write(2, txt, ft_strlen(txt));
		write(2, "\n", 1);
	}
	if (to_free)
		free(to_free);
	if (to_free2)
		free(to_free2);
	return (false);
}

bool	report5(char *error, char *txt, char *to_free, int to_close)
{
	if (g_ok == true)
	{
		write(2, FAIL, ft_strlen(FAIL));
		write(2, "\n", 1);
		g_ok = false;
	}
	if (errno != 0)
	{
		perror(error);
		errno = 0;
	}
	else
	{
		write(2, error, ft_strlen(error));
		write(2, ": ", 2);
		write(2, txt, ft_strlen(txt));
		write(2, "\n", 1);
	}
	if (to_free)
		free(to_free);
	if (to_close)
		close(to_close);
	return (false);
}
