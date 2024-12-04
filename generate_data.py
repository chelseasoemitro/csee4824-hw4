import numpy as np
import sys

import matplotlib.pyplot as plt
import seaborn as sns

UINT32_MAX = 1 << 32
ONE_KB_OF_INTS = 1000 # lower this for plots that don't kill matplotlib

def write_integers(argv):
	if len(argv) != 5 or argv[3].lower() not in {'none', 'partial', 'full'}:
		print(f'usage: python3 {argv[0]} [number of KB] [distribution] [sorting {{none, partial, full}}] [/path/to/output/dir]', file=sys.stderr)
		exit(1)

	num_kb = int(argv[1])
	distribution = argv[2]
	sorting = argv[3].lower()
	output_dir = argv[4]

	rng = np.random.default_rng(0)

	name_to_generator = {
		'normal': lambda: rng.normal(loc=UINT32_MAX // 2, scale=UINT32_MAX // 4, size=ONE_KB_OF_INTS), # normal distribution over 32-bit ints
		'lognormal': lambda: rng.lognormal(mean=20, sigma=0.75, size=ONE_KB_OF_INTS), # long tail
		'uniform': lambda: rng.uniform(high=UINT32_MAX, size=ONE_KB_OF_INTS) # uniform
	}

	values = []
	for i in range(num_kb):
		new_values = name_to_generator[distribution]()
		# some outliers are outside unsigned 32-bit range, manually overflow them
		new_values = map(lambda val: abs(int(val)) % UINT32_MAX, new_values)
		if sorting == 'partial':
			new_values = sorted(new_values)
		values.extend(new_values)
	
	if sorting == 'full':
		values.sort()

	byte_values = map(lambda val: val.to_bytes(4, signed=False), values)

	output_filename = f'{output_dir}/{distribution}_{num_kb}KB'
	sorting_suffix = f'_{sorting}_sorting' if sorting != 'none' else '_no_sorting'

	with open(output_filename + sorting_suffix, 'wb') as output_file:
		for val in byte_values:
			output_file.write(val)


	# charts to include in writeup about our data perhaps
	'''
	sns.barplot(values)
	plt.tight_layout()
	plt.savefig(f'{distribution}{output_suffix}_barplot.png')
	plt.clf()
	sns.histplot(values)
	plt.tight_layout()
	plt.savefig(f'{distribution}{output_suffix}_histplot.png')
	'''


if __name__ == '__main__':
	write_integers(sys.argv)
