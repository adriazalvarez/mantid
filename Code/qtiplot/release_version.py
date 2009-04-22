from datetime import date

vf = open('vers.txt','r')
v = vf.readlines()
f = open('qtiplot/src/Mantid/MantidPlotReleaseDate.h','w')
f.write('#ifndef MANTIDPLOT_RELEASE_DATE\n')
f.write('#define MANTIDPLOT_RELEASE_DATE "')
f.write(date.today().strftime("%d %b %Y"))
f.write(' (Version '+v[0].strip())
f.write(', SVN R'+v[1].strip())
f.write(')')
f.write('"\n#endif\n\n')
f.write('#ifndef MANTIDPLOT_RELEASE_VERSION\n')
f.write('#define MANTIDPLOT_RELEASE_VERSION "')
f.write(v[0].strip()+'.'+v[1].strip())
f.write('"\n#endif\n')
f.close()
