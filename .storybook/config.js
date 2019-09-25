import { configure } from '@storybook/react';
import '../src/style.css';

configure(require.context('../lib/js', true, /\__stories__\/.*.js$/), module);
;