document.addEventListener('DOMContentLoaded', async () => {
    const directionSwitcher = document.getElementsByClassName('direction-icon')[0];
    const directionToggle = document.getElementById('direction-toggle');

    directionSwitcher.addEventListener('click', () => {
        directionToggle.checked = !directionToggle.checked;
        const fromAmount = document.getElementById('amount-input').value;
        const toAmount = document.getElementById('result-output').value;
        const fromCurrency = document.getElementsByClassName('currency-from-text')[0].textContent;
        const toCurrency = document.getElementsByClassName('currency-to-text')[0].textContent;

        document.getElementById('amount-input').value = toAmount;
        document.getElementById('result-output').value = fromAmount;
        document.getElementsByClassName('currency-from-text')[0].textContent = toCurrency;
        document.getElementsByClassName('currency-to-text')[0].textContent = fromCurrency;

        const currencyPairRedirect = document.getElementById('currency-pair-redirect');
        currencyPairRedirect.dataset.from = toCurrency;
        currencyPairRedirect.dataset.to = fromCurrency;

        convertCurrency();
    })

    const currencyPairRedirect = document.getElementById('currency-pair-redirect')

    currencyPairRedirect.addEventListener('click', () => {
        const fromCurrencyName = currencyPairRedirect.dataset.from;
        const toCurrencyName = currencyPairRedirect.dataset.to;
        console.log(fromCurrencyName, toCurrencyName);
        currencyPairRedirect.href = `/currency?c1=${fromCurrencyName}&c2=${toCurrencyName}`;
    });

    document.getElementById('amount-input').addEventListener('input', convertCurrency);

    const currencyPopup = document.getElementById('currency-popup');
    const currencyList = document.getElementById('currency-list');
    const searchInput = document.getElementById('currency-search-input');
    const closePopupBtn = document.getElementsByClassName('close-popup')[0];

    let currencies = await loadCurrencies();
    let currentlySelectingFor = 'from';

    document.getElementsByClassName('currency-from-text')[0].addEventListener('click', () => {
        currentlySelectingFor = 'from';
        openCurrencyPopup();
    });

    document.getElementsByClassName('currency-to-text')[0].addEventListener('click', () => {
        currentlySelectingFor = 'to';
        openCurrencyPopup();
    });

    closePopupBtn.addEventListener('click', () => {
        currencyPopup.classList.remove('active');
        convertCurrency();
    });

    currencyPopup.addEventListener('click', (event) => {
        if (event.target === currencyPopup) {
            currencyPopup.classList.remove('active');
            convertCurrency();
        }
    });

    searchInput.addEventListener('input', () => {
        const searchTerm = searchInput.value.toLowerCase();
        renderCurrencyList(searchTerm);
    });

    function selectCurrency(code) {
        if (currentlySelectingFor === 'from') {
            document.getElementsByClassName('currency-from-text')[0].textContent = code;
            currencyPairRedirect.dataset.from = code;
        } else {
            document.getElementsByClassName('currency-to-text')[0].textContent = code;
            currencyPairRedirect.dataset.to = code;
        }

        currencyPopup.classList.remove('active');
        convertCurrency();
    }

    function renderCurrencyList(searchTerm = '') {
        currencyList.innerHTML = '';

        Object.entries(currencies).forEach(([code, name]) => {
            if (searchTerm && !code.toLowerCase().includes(searchTerm) && !name.toLowerCase().includes(searchTerm)) {
                return;
            }

            const currencyItem = document.createElement('div');
            currencyItem.className = 'currency-item';
            currencyItem.innerHTML = `
                <span class="currency-code">${code.toUpperCase()}</span>
                <span class="currency-name">${name}</span>
            `;

            currencyItem.addEventListener('click', () => {
                selectCurrency(code.toUpperCase());
            });

            currencyList.appendChild(currencyItem);
        });
    }

    function openCurrencyPopup() {
        searchInput.value = '';
        renderCurrencyList();
        currencyPopup.classList.add('active');
    }
})

async function loadCurrencies() {
    let currencies = {};
    try {
        const response = await fetch('/api/currencies');
        if (!response.ok) {
            console.error('Error loading list of currencies');
        } else {
            currencies = await response.json();
            console.log('Currencies list loaded:', currencies);
        }
    } catch (error) {
        console.error('Error loading list of currencies:', error);
    }
    return currencies;
}

async function convertCurrency() {
    const amount = document.getElementById('amount-input').value || 1;
    const fromCurrency = document.getElementsByClassName('currency-from-text')[0].textContent.toLowerCase();
    const toCurrency = document.getElementsByClassName('currency-to-text')[0].textContent.toLowerCase();

    console.log(`Converting ${amount} ${fromCurrency} to ${toCurrency}`);

    try {
        const response = await fetch(`/api/currencies/${fromCurrency}`);

        if (!response.ok) {
            console.error('Error loading currency data');
        } else {
            const data = await response.json();

            if (data && data[fromCurrency] && data[fromCurrency][toCurrency]) {
                const rate = data[fromCurrency][toCurrency];

                document.getElementById('result-output').value = (amount * rate).toFixed(4);

                const pairRateValue = document.getElementsByClassName('pair-rate-data')[0].getElementsByTagName('p')[0];
                pairRateValue.textContent = rate.toFixed(4);

                const pairRateHeader = document.getElementsByClassName('pair-rate-data')[0].getElementsByTagName('h2')[0];
                pairRateHeader.textContent = `${fromCurrency.toUpperCase()}/${toCurrency.toUpperCase()}`;
            } else {
                console.error('No exchange rate data for selected currency pair');
            }
        }
    } catch (error) {
        console.error('Error converting currency:', error);
    }
}