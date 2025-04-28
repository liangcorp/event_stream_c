unsigned int f_randi(unsigned int index)
{
	index = (index << 13) ^ index;
	return ((index * (index * index * 15731 + 789221) + 1376312589) &
		0x7fffffff);
}
