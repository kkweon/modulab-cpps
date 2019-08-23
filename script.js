/**
 * Helper function to create =HYPERLINK links for Google Spreadsheets;
 *
 * How to use:
 *
 * (0) Go to a markdown page (e.g., chapter2.md)
 * (1) Open Developer Console on the browser
 * (2) Copy the code and Paste the output to the spreadsheet
 */
function getTimeComplexity(anchor) {
  try {
    return anchor.parentElement.nextElementSibling.firstElementChild.textContent
      .replace(/time:/i, '')
      .trim();
  } catch (e) {
    console.error(e);
    return 'NA';
  }
}

function getSpaceComplexity(anchor) {
  try {
    return anchor.parentElement.nextElementSibling.firstElementChild.nextElementSibling.textContent
      .replace(/space:/i, '')
      .trim();
  } catch (e) {
    console.error(e);
    return 'NA';
  }
}

{
  const anchors = [...document.querySelectorAll('.markdown-body h2 .anchor')];
  const ret = anchors
    .map(a => {
      const t = getTimeComplexity(a);
      const s = getSpaceComplexity(a);

      return `=HYPERLINK("${a.href}", "${t} / ${s}")`;
    })
    .join('\t');

  console.log(ret);
}
